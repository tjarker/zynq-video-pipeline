#include <stdint.h>
#include <hls_stream.h>
#include <ap_axi_sdata.h>
#include "hls_print.h"

#define WIDTH 1280
#define HEIGHT 720

#define GR(v) ((v)&0xFF)
#define GG(v) (((v)&0xFF00)>>8)
#define GB(v) (((v)&0xFF0000)>>16)
#define SR(v) ((v)&0xFF)
#define SG(v) (((v)&0xFF)<<8)
#define SB(v) (((v)&0xFF)<<16)

#define MAX_PXL_CNT (WIDTH * HEIGHT)
#define in_range(x, a, b) ((x) >= (a + MAX_PXL_CNT - 1) && (x) <= (b + MAX_PXL_CNT - 1))
#define at(x, a) (x == (a + MAX_PXL_CNT - 1))

// #define PRINT

#ifdef PRINT
#define debug(x) std::cout << x << std::endl;
#else
#define debug(x)
#endif

typedef ap_axiu<32,1,1,1> pixel_data;
typedef hls::stream<pixel_data> pixel_stream;
typedef ap_ufixed<16, 8> fixed_t;

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} vec3_u8_t;

typedef struct {
	uint32_t r;
	uint32_t g;
	uint32_t b;
} vec3_u32_t;

typedef struct {
	ap_uint<20> r;
	ap_uint<20> g;
	ap_uint<20> b;
} vec3_u20_t;

typedef struct {
	fixed_t r;
	fixed_t g;
	fixed_t b;
} vec3_fixed_t;

typedef ap_uint<20> hist_t;

void contrast (pixel_stream &src, pixel_stream &dst, bool bypass, ap_ufixed<8, 0> f) {
#pragma HLS interface s_axilite port=f
#pragma HLS interface s_axilite port=bypass
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis port=src
#pragma HLS INTERFACE axis port=dst
#pragma HLS PIPELINE II=1


	// histogram memories
	static hist_t hist_r[256], hist_g[256], hist_b[256];

	// histogram increment pipeline registers
	static vec3_u8_t hist_buf_indices = {0,0,0};
	static vec3_u20_t hist_buf = {0,0,0};

	// contrast enhancement parameters
	static vec3_u8_t first = {0,0,0}, last = {255,255,255};
	static uint8_t stop_r, stop_g, stop_b;
	static hist_t max_b = 0, max_g = 0, max_r = 0;
	static hist_t threshold_b = 0, threshold_g = 0, threshold_r = 0;
	static vec3_fixed_t scale = {2.0,2.0,2.0};
	static vec3_u8_t lower = {0,0,0};
	static vec3_u8_t upper = {255,255,255};

	static uint32_t pxl_cnt = 0;
	static uint8_t counter;

	pixel_data p;
	uint8_t r_in,g_in,b_in;
	uint8_t r_out,g_out,b_out;


#pragma HLS DEPENDENCE variable=hist_buf intra RAW false


	// load pixel data from source
	src >> p;
	r_in = GR(p.data);
	b_in = GB(p.data);
	g_in = GG(p.data);

	// reset X and Y counters on user signal
	if (p.user){
		pxl_cnt = 0;
		hist_buf.r = 0;
		hist_buf.g = 0;
		hist_buf.b = 0;
	}


	{ // computation of output pixel data

		// calculate scaled and offset pixel data
		int16_t enhanced_r = ((r_in * scale.r)) - lower.r;
		int16_t enhanced_g = ((g_in * scale.g)) - lower.g;
		int16_t enhanced_b = ((b_in * scale.b)) - lower.b;

		uint8_t r = enhanced_r > 255 ? 255 : enhanced_r < 0 ? 0 : enhanced_r;
		uint8_t g = enhanced_g > 255 ? 255 : enhanced_g < 0 ? 0 : enhanced_g;
		uint8_t b = enhanced_b > 255 ? 255 : enhanced_b < 0 ? 0 : enhanced_b;

		// apply thresholding
		r_out = r_in < lower.r ? 0 : r_in > upper.r ? 255 : r;
		g_out = g_in < lower.g ? 0 : g_in > upper.g ? 255 : g;
		b_out = b_in < lower.b ? 0 : b_in > upper.b ? 255 : b;

		// compose pixel data
		if (!bypass) p.data = SR(r_out) | SG(g_out) | SB(b_out);

		// push pixel to output stream
		dst << p;
	}
	
	// contrast parameter calcultion steps
	if (pxl_cnt < (MAX_PXL_CNT - 1 - 514)) { // collect histogram data

		hist_r[hist_buf_indices.r] = hist_buf.r + 1;
		hist_g[hist_buf_indices.g] = hist_buf.g + 1;
		hist_b[hist_buf_indices.b] = hist_buf.b + 1;
		
		hist_buf_indices.r = r_in;
		hist_buf_indices.g = g_in;
		hist_buf_indices.b = b_in;

		hist_buf.r = hist_r[r_in]; // forwarding is implicit since we first write and then read
		hist_buf.g = hist_g[g_in];
		hist_buf.b = hist_b[b_in];

	} else if (at(pxl_cnt, -514)) { // reset max's

		max_r = 0;
		max_g = 0;
		max_b = 0;
		counter = 0;

		debug("reset");

	} else if (in_range(pxl_cnt, -513, -258)){ // find max's

		hist_t count_r = hist_r[counter];
		hist_t count_g = hist_g[counter];
		hist_t count_b = hist_b[counter];

		if(max_r < count_r){
			max_r = count_r;
		}

		if(max_g < count_g){
			max_g = count_g;
		}

		if(max_b < count_b){
			max_b = count_b;
		}

		counter++;

	} else if (at(pxl_cnt, -257)) { // calculate thresholds

		threshold_r = max_r * f;
		threshold_g = max_g * f;
		threshold_b = max_b * f;

		first.r = 0;
		last.r = 255;
		first.b = 0;
		last.b = 255;
		first.g = 0;
		last.g = 255;

		stop_r = 0;
		stop_g = 0;
		stop_b = 0;

		counter = 0;

		debug("max_b = " << max_b);
		debug("threshold_b = " << threshold_b);

	} else if (in_range(pxl_cnt, -256, -1)){ // find first and last
		
		hist_t count_r = hist_r[counter];
		hist_t count_g = hist_g[counter];
		hist_t count_b = hist_b[counter];

		if(count_r > threshold_r && !stop_r){
			first.r = counter;
			stop_r = 1;
		}

		if(count_r > threshold_r){
			last.r = counter;
		}

		if(count_g > threshold_g && !stop_g){
			first.g = counter;
			stop_g = 1;
		}

		if(count_g > threshold_g){
			last.g = counter;
		}

		if(count_b > threshold_b && !stop_b){
			first.b = counter;
			stop_b = 1;
		}

		if(count_b > threshold_b){
			last.b = counter;
		}

		hist_r[counter] = 0;
		hist_g[counter] = 0;
		hist_b[counter] = 0;

		counter++;

	} else if (at(pxl_cnt, 0)) { // calculate scale and offset

		if (first.r == last.r) {
			first.r = 0;
			last.r = 255;
		}
		if (first.g == last.g) {
			first.g = 0;
			last.g = 255;
		}
		if (first.b == last.b) {
			first.b = 0;
			last.b = 255;
		}

		scale.r = (fixed_t(255.0)) / (fixed_t(last.r - first.r));
		scale.b = (fixed_t(255.0)) / (fixed_t(last.b - first.b));
		scale.g = (fixed_t(255.0)) / (fixed_t(last.g - first.g));

		lower.r = first.r;
		lower.g = first.g;
		lower.b = first.b;

		upper.r = last.r;
		upper.g = last.g;
		upper.b = last.b;

		debug("r range = " << (int)first.r << " - " << (int)last.r);
		debug("g range = " << (int)first.g << " - " << (int)last.g);
		debug("b range = " << (int)first.b << " - " << (int)last.b);

		debug("scale_r = " << scale.r);
		debug("scale_g = " << scale.g);
		debug("scale_b = " << scale.b);
	}

	pxl_cnt++;

}


void stream (pixel_stream &src, pixel_stream &dst, int frame) {
	contrast(src, dst, false, 0.08);
}

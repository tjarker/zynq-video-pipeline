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

#define comma_t fixed_t

typedef struct {
	comma_t r;
	comma_t g;
	comma_t b;
} vec3_fixed_t;

void invstripe (pixel_stream &src, pixel_stream &dst, comma_t f)
{
#pragma HLS INTERFACE mode=ap_vld port=f
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis port=src
#pragma HLS INTERFACE axis port=dst
#pragma HLS PIPELINE II=1


	// Data to be stored across 'function calls'
		static uint32_t hist_r[256], hist_g[256], hist_b[256];
		static vec3_u8_t first = {0,0,0}, last = {255,255,255};
		static uint8_t stop_r, stop_g, stop_b;
		static uint32_t max = 0;
		static uint32_t threshold = 0;

		static vec3_fixed_t scale = {2.0,2.0,2.0};
		static vec3_u8_t lower = {0,0,0};
		static vec3_u8_t upper = {255,255,255};

		static uint16_t x = 0;
		static uint16_t y = 0;
		static uint32_t pxl_cnt = 0;
		static uint8_t counter;

		pixel_data p;
		uint8_t r_in,g_in,b_in;
		uint8_t r_out,g_out,b_out;


		// Load pixel data from source
		src >> p;
		r_in = GR(p.data);
		b_in = GB(p.data);
		g_in = GG(p.data);

		// Reset X and Y counters on user signal
		if (p.user){
			x = y = 0;
			pxl_cnt = 0;
		}

		////////////////////////////////
		//COMPUTE NEW INTENSITIES
		{
			// increase histogram entries
			hist_r[r_in]++;
			hist_g[g_in]++;
			hist_b[b_in]++;

			//apply transformation first on blues

			uint8_t enhanced_r = ((r_in * scale.r)) - lower.r;
			uint8_t enhanced_g = ((g_in * scale.g)) - lower.g;
			uint8_t enhanced_b = ((b_in * scale.b)) - lower.b;

			r_out = r_in < lower.r ? 0 : r_in > upper.r ? 255 : enhanced_r;
			g_out = g_in < lower.g ? 0 : g_in > upper.g ? 255 : enhanced_g;
			b_out = b_in < lower.b ? 0 : b_in > upper.b ? 255 : enhanced_b;


			// COMPUTE OUTGOING PIXEL DATA
			uint32_t d = SR(r_out) | SG(g_out) | SB(b_out);
			p.data = d;
			

			// WRITE PIXEL TO DESTINATION
			dst << p;
		}
		

		//SCALE & OFFSET COMPUTATION
		//first find MAX in blues histograms

		if (at(pxl_cnt, -514)) {

			max = 0;
			counter = 0;

			debug("reset");

		} else if (in_range(pxl_cnt, -513, -258)){

			uint32_t count_r = hist_r[counter];
			uint32_t count_g = hist_g[counter];
			uint32_t count_b = hist_b[counter];

			if(max < count_b){
				max = count_b;
			}

			counter++;

		} else if (at(pxl_cnt, -257)) {

			threshold = max * f;

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

			debug("max = " << max);
			debug("threshold = " << threshold);

		} else if (in_range(pxl_cnt, -256, -1)){
			
			uint32_t count_r = hist_r[counter];
			uint32_t count_g = hist_g[counter];
			uint32_t count_b = hist_b[counter];

			if(count_r > threshold && !stop_r){
				first.r = counter;
				stop_r = 1;
			}

			if(count_r > threshold){
				last.r = counter;
			}

			if(count_g > threshold && !stop_g){
				first.g = counter;
				stop_g = 1;
			}

			if(count_g > threshold){
				last.g = counter;
			}

			if(count_b > threshold && !stop_b){
				first.b = counter;
				stop_b = 1;
			}

			if(count_b > threshold){
				last.b = counter;
			}

			hist_r[counter] = 0;
			hist_g[counter] = 0;
			hist_b[counter] = 0;

			counter++;

		} else if (at(pxl_cnt, 0)) {

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

			scale.r = (comma_t(255.0)) / (comma_t(last.r - first.r));
			scale.b = (comma_t(255.0)) / (comma_t(last.g - first.g));
			scale.g = (comma_t(255.0)) / (comma_t(last.b - first.b));

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
		

		// Increment X and Y counters
		pxl_cnt++;

		if (p.last) {
			x = 0;
			y++;
		} else {
			x++;
		}

}

void stream (pixel_stream &src, pixel_stream &dst, int frame)
{
	invstripe(src, dst, 0.01);
}

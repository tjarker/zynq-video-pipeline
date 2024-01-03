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
typedef ap_fixed<16, 8> fixed_t;

void invstripe (pixel_stream &src, pixel_stream &dst, float f)
{
#pragma HLS INTERFACE mode=ap_vld port=f
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis port=src
#pragma HLS INTERFACE axis port=dst
#pragma HLS PIPELINE II=1


	// Data to be stored across 'function calls'
		static uint32_t hist_r[256], hist_g[256], hist_b[256];
		static uint16_t x = 0;
		static uint16_t y = 0;
		static uint32_t pxl_cnt = 0;
		static uint32_t max = 0;
		static uint8_t first_r = 0;
		static uint8_t last_r = 255;
		static uint8_t first_b = 0;
		static uint8_t last_b = 255;
		static uint8_t first_g = 0;
		static uint8_t last_g = 255;
		static float scale_r = 2;
		static float scale_g = 2;
		static float scale_b = 2;
		static uint8_t offset_r = 0;
		static uint8_t offset_g = 0;
		static uint8_t offset_b = 0;
		static uint8_t counter;
		static uint8_t stop_r, stop_g, stop_b;
		static uint32_t threshold = 0;

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
		if(y < HEIGHT - 1){

			// increase histogram entries
			hist_r[r_in]++;
			hist_g[g_in]++;
			hist_b[b_in]++;

			//apply transformation first on blues

			r_out = r_in < first_r ? 0 : r_in > last_r ? 255 : ((r_in * scale_r)) - offset_r;
			g_out = g_in < first_g ? 0 : g_in > last_g ? 255 : ((g_in * scale_g)) - offset_g;
			b_out = b_in < first_b ? 0 : b_in > last_b ? 255 : ((b_in * scale_b)) - offset_b;


			// COMPUTE OUTGOING PIXEL DATA
			uint32_t d = SR(r_out) | SG(g_out) | SB(b_out);
			p.data = d;
		}

		// WRITE PIXEL TO DESTINATION
		dst << p;

		

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

			first_r = 10;
			last_r = 255;
			first_b = 10;
			last_b = 255;
			first_g = 10;
			last_g = 255;

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
				first_r = counter;
				stop_r = 1;
			}
													//128 = 10000000
			if(count_r > threshold){
				last_r = counter;
			}
													//2 = 00000010
			if(count_g > threshold && !stop_g){
				first_g = counter;
				stop_g = 1;
			}

													//64 = 01000000
			if(count_g > threshold){
				last_g = counter;
			}
													//4 = 00000100
			if(count_b > threshold && !stop_b){
				first_b = counter;
				stop_b = 1;
			}
													//32 = 00100000
			if(count_b > threshold){
				last_b = counter;
			}

			counter++;

		} else if (at(pxl_cnt, 0)) {

			scale_r = 255/((float) (last_r - first_r));
			scale_b = 255/((float) (last_g - first_g));
			scale_g = 255/((float) (last_b - first_b));

			offset_r = first_r;
			offset_g = first_g;
			offset_b = first_b;

			debug("r range = " << (int)first_r << " - " << (int)last_r);
			debug("g range = " << (int)first_g << " - " << (int)last_g);
			debug("b range = " << (int)first_b << " - " << (int)last_b);

			debug("scale_r = " << scale_r);
			debug("scale_g = " << scale_g);
			debug("scale_b = " << scale_b);
		}
		

		// Increment X and Y counters
		pxl_cnt++;
		if (p.last)
		{
			x = 0;
			y++;
		}
		else
			x++;

}

void stream (pixel_stream &src, pixel_stream &dst, int frame)
{
	invstripe(src, dst, 0.01);
}

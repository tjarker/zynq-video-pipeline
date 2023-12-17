#include <stdint.h>
#include <hls_stream.h>
#include <ap_axi_sdata.h>

#define WIDTH 1280
#define HEIGHT 720

#define GR(v) ((v)&0xFF)
#define GG(v) (((v)&0xFF00)>>8)
#define GB(v) (((v)&0xFF0000)>>16)
#define SR(v) ((v)&0xFF)
#define SG(v) (((v)&0xFF)<<8)
#define SB(v) (((v)&0xFF)<<16)

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
		static uint32_t hist[3][256];
		static uint16_t x = 0;
		static uint16_t y = 0;
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
		static uint16_t counter;
		static uint8_t stop;
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

		}

		////////////////////////////////
		//COMPUTE NEW INTENSITIES
		if(y < HEIGHT - 1){

			// increase histogram entries
			hist[2][r_in]++;
			hist[1][g_in]++;
			hist[0][b_in]++;

			//apply transformation first on blues

			r_out = r_in < first_r ? 0 : r_in > last_r ? 255 : ((r_in * scale_r)) - first_r;
			g_out = g_in < first_g ? 0 : g_in > last_g ? 255 : ((g_in * scale_g)) - first_g;
			b_out = b_in < first_b ? 0 : b_in > last_b ? 255 : ((b_in * scale_b)) - first_b;


			// COMPUTE OUTGOING PIXEL DATA
			uint32_t d = SR(r_out) | SG(g_out) | SB(b_out);
			p.data = d;
		}

		//SCALE & OFFSET COMPUTATION
		//first find MAX in blues histograms
		if(y == HEIGHT - 1){
			if(x >= WIDTH - 514 and x < WIDTH - 257){
				counter = x - WIDTH + 514;
				if(max < hist[0][counter]){
					max = hist[0][counter];
				}
				if(counter == 255){
					threshold = max * f;
					stop = 0;
				}
			}

			//find FIRTS and LAST
		    //stop = 00000000  							231 = 11100111
			if(x >= WIDTH - 257 and x < WIDTH - 129 and stop != 231){
				counter = x - WIDTH + 257;
													//1 = 00000001
				if(hist[0][counter] > threshold and !(stop & 1)){
					first_b = counter;
					stop = 1 | stop;
				}
														//128 = 10000000
				if(hist[0][255-counter] > threshold and !(stop & 128)){
					last_b = 255 - counter;
					stop = 128 | stop;
				}
														//2 = 00000010
				if(hist[1][counter] > threshold and !(stop & 2)){
					first_g = counter;
					stop = 2 | stop;
				}

														//64 = 01000000
				if(hist[1][255-counter] > threshold and !(stop & 64)){
					last_g = 255 - counter;
					stop = 64 | stop;
				}
														//4 = 00000100
				if(hist[2][counter] > threshold and !(stop & 4)){
					first_r = counter;
					stop = 4 | stop;
				}
														//32 = 00100000
				if(hist[2][255-counter] > threshold and !(stop & 32)){
					last_r = 255 - counter;
					stop = 32 | stop;
				}
			}

			if(stop == 231){
				scale_r = 255/(last_r - first_r);
				scale_b = 255/(last_b - first_b);
				scale_g = 255/(last_g - first_g);
			}


			if(x >= WIDTH - 129){
				counter = x - WIDTH + 129;
				hist[0][counter] = 0;
				hist[0][255-counter] = 0;
				hist[1][counter] = 0;
				hist[1][255-counter] = 0;
				hist[2][counter] = 0;
				hist[2][255-counter] = 0;
			}
		}


		////////////////////////////////

		// WRITE PIXEL TO DESTINATION
		dst << p;

		// Increment X and Y counters
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
	invstripe(src, dst, 0.02);
}

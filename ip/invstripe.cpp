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

void invstripe (pixel_stream &src, pixel_stream &dst, float f)
{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis port=&src
#pragma HLS INTERFACE axis port=&dst
#pragma HLS INTERFACE s_axilite port=f
#pragma HLS PIPELINE II=1


	// Data to be stored across 'function calls'
		static uint32_t hist[3][256];
		static uint16_t x = 0;
		static uint16_t y = 0;
		static uint32_t max = 0;
		static uint8_t first_r = 50;
		static uint8_t last_r = 205;
		static uint8_t first_b = 50;
		static uint8_t last_b = 205;
		static uint8_t first_g = 50;
		static uint8_t last_g = 205;
		static float scale_r = 1.645;
		static float scale_g = 1.645;
		static float scale_b = 1.645;
		static uint16_t counter;
		static uint8_t stop = 0;
		static uint16_t threshold = 0;

		pixel_data p;
		uint8_t r,g,b;


		// Load pixel data from source
		src >> p;
		r = GR(p.data);
		b = GB(p.data);
		g = GG(p.data);

		// Reset X and Y counters on user signal
		if (p.user){
			x = y = 0;
			max = 0;
			stop = 0;

		}

		////////////////////////////////
		//COMPUTE NEW INTENSITIES
		if(y < HEIGHT - 1){

			// increase histogram entries
			hist[2][GR(p.data)]++;
			hist[1][GG(p.data)]++;
			hist[0][GB(p.data)]++;

			//apply transformation first on blues
			r = r < first_r ? 0 : r > last_r ? 255 : (r * scale_r) - first_r;
			g = g < first_g ? 0 : g > last_g ? 255 : (g  * scale_g) - first_g;
			b = b < first_b ? 0 : b > last_b ? 255 : (b * scale_b) - first_b;


			// COMPUTE OUTGOING PIXEL DATA
			uint32_t d = SR(r) | SG(g) | SB(b);
			p.data = d;
		}

		//SCALE & OFFSET COMPUTATION
		//first find MAX in blues histograms
		if(y == HEIGHT - 1){
			if(x >= WIDTH - 514 and x < WIDTH - 257){
				counter = x - WIDTH + 514;
				max = max < hist[0][counter]?hist[0][counter]: max;
				threshold = counter == 255? max * f : 0;
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
				scale_r = 255.0f/(last_r - first_r);
				scale_b = 255.0f/(last_b - first_b);
				scale_g = 255.0f/(last_g - first_g);
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
	invstripe(src, dst, 0.01);
}

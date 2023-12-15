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

		pixel_data p;
		uint8_t r,g,b;
		uint8_t stop = 0;



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
		if(y < HEIGHT - 1 and x < WIDTH - 514){

			// increase histogram entries
			hist[2][GR(p.data)]++;
			hist[1][GG(p.data)]++;
			hist[0][GB(p.data)]++;

			//apply transformation first on blues
			if(GB(p.data) < first_b){
				b = 0;
			}
			if(GB(p.data) > last_b){
				b = 255;
			}
			if(GB(p.data)< last_b and GB(p.data) > first_b){
				b = (scale_b*GB(p.data)) - first_b;
			}

			//then on greens
			if(GG(p.data) < first_g){
				g = 0;
			}
			if(GG(p.data) > last_g){
				g = 255;
			}
			if(GG(p.data)< last_g and GG(p.data) > first_g){
				g = (scale_g*GG(p.data)) - first_g;
			}

			//and finally on reds
			if(GR(p.data) < first_r){
				r = 0;
			}
			if(GR(p.data) > last_r){
				r = 255;
			}
			if(GR(p.data)< last_r and GR(p.data) > first_r){
				r = (scale_r*GR(p.data)) - first_r;
			}

			// COMPUTE OUTGOING PIXEL DATA
			uint32_t d = SB(b) + SG(g) + SR(r);
			p.data = d;
		}

		//SCALE & OFFSET COMPUTATION
		//first find MAX in blues histograms
		if(y == HEIGHT - 1){
			if(x >= WIDTH - 514 and x < WIDTH - 257){
				counter = x - WIDTH + 514;
				if(hist[0][counter] > max){
					max = hist[0][counter];
				}
			}

			//find FIRTS and LAST
			if(x >= WIDTH - 257 and x < WIDTH - 129){
				uint16_t threshold = max * f;
				counter = x - WIDTH + 257;
				if(hist[0][counter] > threshold and ((stop and 1) == 0)){
					first_b = counter;
					stop = 1 or stop;
				}
				if(hist[0][255-counter] > threshold and ((stop and 128) == 0)){
					last_b = 255 - counter;
					stop = 128 or stop;
				}
				if(hist[1][counter] > threshold and ((stop and 2) == 0)){
					first_g = counter;
					stop = 2 or stop;
				}
				if(hist[1][255-counter] > threshold and ((stop and 64) == 0)){
					last_g = 255 - counter;
					stop = 64 or stop;
				}
				if(hist[2][counter] > threshold and ((stop and 4) == 0)){
					first_r = counter;
					stop = 4 or stop;
				}
				if(hist[2][255-counter] > threshold and ((stop and 32) == 0)){
					last_r = 255 - counter;
					stop = 32 or stop;
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
	invstripe(src, dst, 0.001);
}

#include <stdint.h>
#include <hls_stream.h>
#include <ap_axi_sdata.h>

#define WIDTH 1280
#define HEIGHT 720

typedef ap_axiu<32,1,1,1> pixel_data;
typedef hls::stream<pixel_data> pixel_stream;

void convo (pixel_stream &src, pixel_stream &dst) {
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis port=src
#pragma HLS INTERFACE axis port=dst
#pragma HLS PIPELINE II=1

	static uint16_t head_y; // y coordinate on the receiving end
	static uint16_t tail_y = 1; // y coordinate on the sending end (starts non-zero to avoid asserting user signal without new frame)
	static uint16_t x; // shared x coordinate
	
	// Buffer to 4 lines of pixels
	// the buffer is addressed by the lower two bits of a y coordinate
	static uint32_t buf[4][WIDTH];
	#pragma HLS DEPENDENCE variable=buf intra RAW false

	// Read data from stream
	pixel_data p_in;
	src >> p_in;

	// synchronize with stream
	if (p_in.user) {
		head_y = 0;
		x = 0;
	}

	// Store data to buffer
	buf[head_y % 4][x] = p_in.data;

	
	// Read data from buffer
	uint32_t input = buf[tail_y % 4][x];

	// Process data
	uint32_t output = ~input;


	// Write data to stream
	pixel_data p_out;
	p_out.data = output;
	p_out.user = tail_y == 0 && x == 0; // new frame on output stream
	p_out.last = p_in.last; // lines are output in sync with input stream
	dst << p_out;
	
	
	// manage tail coordinate
	if (head_y == 2 && p_in.last) { // start processing a new frame next cycle
		tail_y = 0;
	} else if (p_in.last) {
		tail_y++;
	}

	// manage head coordinates
	if (p_in.last) {
		x = 0;
		head_y++;
	} else {
		x++;
	}

}

void stream (pixel_stream &src, pixel_stream &dst, int frame) {
	convo(src, dst);
}

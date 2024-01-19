#include <stdint.h>
#include <hls_stream.h>
#include <ap_axi_sdata.h>

#define WIDTH 1280
#define HEIGHT 720

#define getColor(b) (*((color_t*)(&b)))
#define get24bits(c) (*((uint32_t*)(&c)))

typedef ap_axiu<32,1,1,1> pixel_data;
typedef hls::stream<pixel_data> pixel_stream;

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} color_t;

void convo (pixel_stream &src, pixel_stream &dst, bool bypass = true) {
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS interface s_axilite port=bypass
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
	#pragma HLS ARRAY_PARTITION variable=buf dim=1 block factor=4
	#pragma HLS ARRAY_PARTITION variable=buf dim=2 cyclic factor=4

	color_t black = {0};

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
	uint32_t center_port = buf[tail_y % 4][x];
	uint32_t left_port = x == 0 ? 0 : buf[tail_y % 4][x - 1];
	uint32_t right_port = x == (WIDTH - 1) ? 0 : buf[tail_y % 4][x + 1];
	uint32_t top_port = tail_y == 0 ? 0 : buf[(tail_y - 1) % 4][x];
	uint32_t bottom_port = tail_y == (HEIGHT - 1) ? 0 : buf[(tail_y + 1) % 4][x];
	
	color_t center = getColor(center_port);
	color_t left = getColor(left_port);
	color_t right = getColor(right_port);
	color_t top = getColor(top_port);
	color_t bottom = getColor(bottom_port);

	// Process data
	color_t out;
	int16_t r = 5 * int16_t(center.r) - left.r - right.r - top.r - bottom.r;
	int16_t g = 5 * int16_t(center.g) - left.g - right.g - top.g - bottom.g;
	int16_t b = 5 * int16_t(center.b) - left.b - right.b - top.b - bottom.b;

	out.r = r > 255 ? 255 : r < 0 ? 0 : r;
	out.g = g > 255 ? 255 : g < 0 ? 0 : g;
	out.b = b > 255 ? 255 : b < 0 ? 0 : b;


	// Write data to stream
	pixel_data p_out;
	p_out.data = bypass ? center_port : get24bits(out);
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

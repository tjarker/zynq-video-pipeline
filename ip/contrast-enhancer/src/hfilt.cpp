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

typedef ap_axiu<32, 1, 1, 1> pixel_data;
typedef hls::stream <pixel_data> pixel_stream;

void hfilt(pixel_stream &src, pixel_stream &dst, uint8_t l, uint8_t c, uint8_t r) {
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis port=&src
#pragma HLS INTERFACE axis port=&dst
#pragma HLS INTERFACE s_axilite port=l
#pragma HLS INTERFACE s_axilite port=c
#pragma HLS INTERFACE s_axilite port=r
#pragma HLS PIPELINE II=1

    // Data to be stored across 'function calls'
    static uint16_t x = 0;
    static uint16_t y = 0;

    pixel_data p_in;

    // Load input data from source
    src >> p_in;

    // Reset X and Y counters on user signal
    if (p_in.user)
        x = y = 0;

    ////////////////////////////////

    // Pixel data to be stored across 'function calls'
    static pixel_data p_out;

    uint8_t first = 20;
    uint8_t last = 255 - 20;
    uint16_t scaler = 255 / (last - first);
    uint16_t offset = first;


    // Current (incoming) pixel data
    uint32_t dr = p_in.data;

    uint8_t red = GR(dr);
    uint8_t green = GG(dr);
    uint8_t blue = GB(dr);

    uint8_t out_red = red < first ? 0 : red > last ? 255 : (red * scaler) - offset;
    uint8_t out_green = green < first ? 0 : green > last ? 255 : (green  * scaler) - offset;
    uint8_t out_blue = blue < first ? 0 : blue > last ? 255 : (blue * scaler) - offset;


    uint32_t dn = SR(out_red) | SG(out_green) | SB(out_blue);

    p_out.data = dn;

    ////////////////////////////////

    // Write pixel to destination
    dst << p_out;

    // Copy previous pixel data to next output pixel
    p_out = p_in;

    // Increment X and Y counters
    if (p_in.last) {
        x = 0;
        y++;
    } else {
        x++;
    }
}

void stream(pixel_stream &src, pixel_stream &dst, int frame) {
    hfilt(src, dst, 50, 150, 50);
}

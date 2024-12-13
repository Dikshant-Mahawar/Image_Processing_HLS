#include "sepia_filter.h"

// Function to convert a pixel's RGB values to sepia
void sepia_filter(unsigned char red, unsigned char green, unsigned char blue,
                  unsigned char *newRed, unsigned char *newGreen, unsigned char *newBlue)
{
    #pragma HLS INTERFACE ap_none port=red
    #pragma HLS INTERFACE ap_none port=green
    #pragma HLS INTERFACE ap_none port=blue
    #pragma HLS INTERFACE ap_none port=newRed
    #pragma HLS INTERFACE ap_none port=newGreen
    #pragma HLS INTERFACE ap_none port=newBlue
    #pragma HLS INTERFACE ap_none port=return

    // Calculate the sepia tones
    unsigned char tr = (unsigned char)(0.393 * red + 0.769 * green + 0.189 * blue);
    unsigned char tg = (unsigned char)(0.349 * red + 0.686 * green + 0.168 * blue);
    unsigned char tb = (unsigned char)(0.272 * red + 0.534 * green + 0.131 * blue);

    // Clamp values to be within the range of 0 to 255
    *newRed = (tr > 255) ? 255 : tr;
    *newGreen = (tg > 255) ? 255 : tg;
    *newBlue = (tb > 255) ? 255 : tb;
}

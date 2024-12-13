#include "grayscale_filter.h"

// Function to convert a pixel's RGB values to grayscale
unsigned char grayscale_filter(int red, int green, int blue) {


	#pragma HLS INTERFACE ap_none port=red
    #pragma HLS INTERFACE ap_none port=green
    #pragma HLS INTERFACE ap_none port=blue
    #pragma HLS INTERFACE ap_none port=return

    unsigned char gray = (unsigned char)(0.299 * red + 0.587 * green + 0.114 * blue);

    return gray;
}

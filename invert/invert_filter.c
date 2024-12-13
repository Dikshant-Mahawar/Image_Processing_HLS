#include "invert_filter.h"

// Function to invert a pixel's RGB values
void invert_filter(unsigned char red, unsigned char green, unsigned char blue,
                   unsigned char *newRed, unsigned char *newGreen, unsigned char *newBlue)
{
    #pragma HLS INTERFACE ap_none port=red
    #pragma HLS INTERFACE ap_none port=green
    #pragma HLS INTERFACE ap_none port=blue
    #pragma HLS INTERFACE ap_none port=newRed
    #pragma HLS INTERFACE ap_none port=newGreen
    #pragma HLS INTERFACE ap_none port=newBlue
    #pragma HLS INTERFACE ap_none port=return

    // Calculate the inverted colors
    *newRed = 255 - red;
    *newGreen = 255 - green;
    *newBlue = 255 - blue;
}


#include <stdio.h>
#include "grayscale_filter.h"

#define MAX_HEIGHT 5
#define MAX_WIDTH 5

// Predefined frame with RGB pixels (5x5)
int frame_in[MAX_HEIGHT][MAX_WIDTH][3] = {
    {{120, 100, 80}, {200, 150, 100}, {220, 180, 130}, {100, 50, 30}, {50, 30, 20}},
    {{250, 240, 230}, {130, 120, 110}, {80, 70, 60}, {40, 30, 20}, {200, 190, 180}},
    {{90, 80, 70}, {170, 160, 150}, {210, 200, 190}, {70, 60, 50}, {140, 130, 120}},
    {{160, 150, 140}, {30, 20, 10}, {110, 100, 90}, {220, 210, 200}, {180, 170, 160}},
    {{240, 230, 220}, {60, 50, 40}, {190, 180, 170}, {140, 130, 120}, {120, 110, 100}}
};

// Main function
int main() {
    unsigned char hw_result[5][5], sw_result[5][5];
    int err_cnt = 0;

    // Software simulation loop
    for (int i = 0; i < MAX_HEIGHT; i++) {  // First loop uses 'i'
        for (int j = 0; j < MAX_WIDTH; j++) {
            // Extract the RGB values
            int red = frame_in[i][j][0];
            int green = frame_in[i][j][1];
            int blue = frame_in[i][j][2];

            // Convert RGB to grayscale (Software result)
            unsigned char gray = (unsigned char)(0.299 * red + 0.587 * green + 0.114 * blue);
            sw_result[i][j] = gray;

            // Output the grayscale values for each pixel
            printf("Pixel (%d, %d) Grayscale: R = %d\n", i, j, gray);
        }
    }

#ifdef HW_COSIM
    // Hardware co-simulation loop
    for (int k = 0; k < MAX_HEIGHT; k++) {  // Second loop now uses 'k'
        for (int l = 0; l < MAX_WIDTH; l++) {  // Inner loop uses 'l'
            // Extract the RGB values for hardware simulation
            int red = frame_in[k][l][0];
            int green = frame_in[k][l][1];
            int blue = frame_in[k][l][2];

            // Call the hardware-accelerated grayscale function
            unsigned char gray1 = grayscale_filter(red, green, blue);
            hw_result[k][l] = gray1;
        }
    }
#endif

    // Print result matrix
    printf("{\n");
    for (int m = 0; m < MAX_HEIGHT; m++) {  // Third loop uses 'm'
        printf("{");
        for (int n = 0; n < MAX_WIDTH; n++) {  // Inner loop uses 'n'
#ifdef HW_COSIM
            printf("%d", hw_result[m][n]);
            // Check HW result against SW result
            if (hw_result[m][n] != sw_result[m][n]) {
                err_cnt++;
                printf("*");  // Mark mismatches
            }
#else
            printf("%d", sw_result[m][n]);
#endif
            if (n == MAX_WIDTH - 1)
                printf("}");
            else
                printf(", ");
        }
        printf("\n");
    }
    printf("}\n");

#ifdef HW_COSIM
    if (err_cnt) {
        printf("ERROR: %d mismatches detected!\n", err_cnt);
    } else {
        printf("Test passed.\n");
    }
#endif

    return err_cnt;
}

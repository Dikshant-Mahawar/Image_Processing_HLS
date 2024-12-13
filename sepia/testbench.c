#include <stdio.h>
#include "sepia_filter.h"

#define MAX_HEIGHT 5
#define MAX_WIDTH 5

// Predefined frame with RGB pixels (5x5)
unsigned char frame_in[MAX_HEIGHT][MAX_WIDTH][3] = {
    {{120, 100, 80}, {200, 150, 100}, {220, 180, 130}, {100, 50, 30}, {50, 30, 20}},
    {{250, 240, 230}, {130, 120, 110}, {80, 70, 60}, {40, 30, 20}, {200, 190, 180}},
    {{90, 80, 70}, {170, 160, 150}, {210, 200, 190}, {70, 60, 50}, {140, 130, 120}},
    {{160, 150, 140}, {30, 20, 10}, {110, 100, 90}, {220, 210, 200}, {180, 170, 160}},
    {{240, 230, 220}, {60, 50, 40}, {190, 180, 170}, {140, 130, 120}, {120, 110, 100}}
};

// Main function
int main() {
    unsigned char sw_result[MAX_HEIGHT][MAX_WIDTH][3];
    unsigned char hw_result[MAX_HEIGHT][MAX_WIDTH][3];
    int err_cnt = 0;

    // Software simulation loop
    for (int i = 0; i < MAX_HEIGHT; i++) {
        for (int j = 0; j < MAX_WIDTH; j++) {
            // Extract the RGB values
            unsigned char red = frame_in[i][j][0];
            unsigned char green = frame_in[i][j][1];
            unsigned char blue = frame_in[i][j][2];

            // Apply sepia filter (Software result)
            unsigned char newRed = (unsigned char)(0.393 * red + 0.769 * green + 0.189 * blue);
            unsigned char newGreen = (unsigned char)(0.349 * red + 0.686 * green + 0.168 * blue);
            unsigned char newBlue = (unsigned char)(0.272 * red + 0.534 * green + 0.131 * blue);

            // Clamp values to 255
            sw_result[i][j][0] = (newRed > 255) ? 255 : newRed;
            sw_result[i][j][1] = (newGreen > 255) ? 255 : newGreen;
            sw_result[i][j][2] = (newBlue > 255) ? 255 : newBlue;

            // Output the sepia values for each pixel
            printf("Pixel (%d, %d) Sepia: R = %d, G = %d, B = %d\n", i, j, sw_result[i][j][0], sw_result[i][j][1], sw_result[i][j][2]);
        }
    }

#ifdef HW_COSIM
    // Hardware co-simulation loop
    for (int k = 0; k < MAX_HEIGHT; k++) {
        for (int l = 0; l < MAX_WIDTH; l++) {
            // Extract the RGB values for hardware simulation
            unsigned char red = frame_in[k][l][0];
            unsigned char green = frame_in[k][l][1];
            unsigned char blue = frame_in[k][l][2];

            // Call the hardware-accelerated sepia function
            unsigned char newRed, newGreen, newBlue;
            sepia_filter(red, green, blue, &newRed, &newGreen, &newBlue);

            // Store hardware results and clamp values
            hw_result[k][l][0] = (newRed > 255) ? 255 : newRed;
            hw_result[k][l][1] = (newGreen > 255) ? 255 : newGreen;
            hw_result[k][l][2] = (newBlue > 255) ? 255 : newBlue;
        }
    }
#endif

    // Print result matrix
    printf("{\n");
    for (int m = 0; m < MAX_HEIGHT; m++) {
        printf("{");
        for (int n = 0; n < MAX_WIDTH; n++) {
#ifdef HW_COSIM
            printf("{%d, %d, %d}", hw_result[m][n][0], hw_result[m][n][1], hw_result[m][n][2]);
            // Check HW result against SW result
            if (hw_result[m][n][0] != sw_result[m][n][0] ||
                hw_result[m][n][1] != sw_result[m][n][1] ||
                hw_result[m][n][2] != sw_result[m][n][2]) {
                err_cnt++;
                printf("*");  // Mark mismatches
            }
#else
            printf("{%d, %d, %d}", sw_result[m][n][0], sw_result[m][n][1], sw_result[m][n][2]);
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

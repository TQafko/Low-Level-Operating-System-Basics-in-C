/*
Material by Leonidas Deligiannidis (deligiannidisl@wit.edu) is licensed under a Creative Commons
Attribution-NonCommercial 3.0 Unported License (http://creativecommons.org/licenses/by-nc/3.0/).
*/
//
// This program uses the STB library (http://nothings.org/)
// which points to the code at: https://github.com/nothings/stb
//
// This library enables you to load images (png, jpg, etc).
// You can then manipulate the images at the pixel level.
// Then you can save the pixels as an image.
//
#include "partc.h"
#include <stdio.h>
#include <pthread.h>

// NOLINTBEGIN
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Wdeprecated"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#pragma GCC diagnostic pop

/**
 * This function converts each RGBA value to either 0 or 255 (thus converting an RGB image into an
 * 8-color image).
 *
 * @param data Address of the array
 * @param width Width of the image in pixels
 * @param height Height of the image in pixels
 * @param channels Number of channels per pixel (3 for RGB, 4 for RGBA)
 */
void convert_image(uint8_t* data, int width, int height, int channels) {
    for(int row = 0; row < height; row++) {
        for(int col = 0; col < width; col++) {
            int r_index = (col + width * row) * channels;
            for(int c = 0; c < channels; c++) {
                if( data[r_index+c] > 127 ) {
                    data[r_index+c] = 255;
                } else {
                    data[r_index+c] = 0;
                }
            }
        }
    }
}

/**
 * This program reads an image file, and down-samples each color into an 8-bit
 * color image.
 */
int main(int argc, char *argv[]) {
    if(argc != 3) {
        printf("USAGE:\n  %s IN_FILE OUT_FILE\n", argv[0]);
        return 1;
    }
    const char* infile = argv[1];
    const char* outfile = argv[2];

    // Load the data
    int width = 0;
    int height = 0;
    int channel = 0;
    uint8_t* data = stbi_load(infile, &width, &height, &channel, 0);

    // Convert image
    convert_image(data, width, height, channel);

    // Save the data
    int ret = stbi_write_png(outfile, width, height, channel, data, width * channel);
    if (ret == 0) {
        stbi_image_free(data);
        printf("Error writing file\n");
        return 1;
    }

    // Cleanup
    stbi_image_free(data);
    
	return 0;
}

// NOLINTEND

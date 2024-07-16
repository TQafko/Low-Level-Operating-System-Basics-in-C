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
 * Represents thread arguments for splitting the image processing in 
 * parallel
 * @param data Image pixel values in 24bit format
 * @param width number of pixels in x
 * @param height number of pixels in y
 * @param channels the color format ex. red green blue
 * @param start_row indicating beggining of a row
 * @param end_row indicating end of a row
 */
struct thread_arg {
    unsigned char* data;
    int width;
    int height;
    int channels;
    int start_row;
    int end_row;
};


/**
 * The argument is a struct that contains data about what parts of an
 * image needs to be processes. The rows are the most important in
 * threading and the first loop begings and ends at the start and end
 * of the indicated rows in the struct. The columns and channels are
 * the values of the pixels in each of those rows
 *
 * @param args: The thread arguments containing pixel data, width
 *              height, channels, start_row, end_row
 * @returns NULL
 */
void *thread_main(void *args) {
    struct thread_arg *vals = (struct thread_arg*)args;
    for(int row = vals->start_row; row < vals->end_row; row++) {
        for(int col = 0; col < vals->width; col++) {
            int r_index = (col + vals->width * row) * vals->channels;
            for(int c = 0; c < vals->channels; c++) {
                if( vals->data[r_index+c] > 127 ) {
                    vals->data[r_index+c] = 255;
                } else {
                    vals->data[r_index+c] = 0;
                }
            }
        }
    }
    return NULL;
}

/**
 * This program reads the number of threads to use and an image file. Each thread is assigned 1/4 of
 * the rows of pixels, and down-samples each color pixel into an 8-bit color image.
 */
int main(int argc, char *argv[]) {
    if(argc <= 3) {
        printf("USAGE:\n  %s IN_FILE OUT_FILE NTHREADS\n", argv[0]);
        return 1;
    }
    const char* infile = argv[1];
    const char* outfile = argv[2];
    const char* input = argv[3];

    int nThreads = atoi(input); // Convert string to num

    int width = 0;
    int height = 0;
    int channel = 0;
    uint8_t* data = stbi_load(infile, &width, &height, &channel, 0);

    // Important for splitting threads
    int rowlen = height / nThreads;

    pthread_t *tid = malloc(nThreads*sizeof(pthread_t));
    struct thread_arg *vals = malloc(nThreads*sizeof(struct thread_arg));

    for(int i = 0; i < nThreads; i++){
        vals[i].data = data;
        vals[i].width = width;
        vals[i].height = height;
        vals[i].channels = channel;
        vals[i].start_row = rowlen * i;
        vals[i].end_row = vals[i].start_row + rowlen;
        if ((i == (nThreads - 1)) && ((vals[i].height % nThreads) != 0)) {
            vals[i].end_row = vals[i].start_row + rowlen + (vals[i].height % nThreads);
        }
        pthread_create(&tid[i], NULL, &thread_main, &vals[i]);
    }

    for(int i = 0; i < nThreads; i++){
        pthread_join(tid[i], NULL);
    }

    // Save the data
    int ret = stbi_write_png(outfile, width, height, channel, data, width * channel);
    if (ret == 0) {
        stbi_image_free(data);
        printf("Error writing file\n");
        return 1;
    }

    // Cleanup
    stbi_image_free(data);
    free(tid);
    free(vals);
    
	return 0;
}

// NOLINTEND

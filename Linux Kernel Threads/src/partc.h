#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h> // For true/false
#include <stdlib.h> // For malloc/free
#include <stdint.h> // For uint8_t type

void convert_image(uint8_t* data, int width, int height, int channels);

#ifdef __cplusplus
}
#endif

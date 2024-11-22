#ifndef COLOR_DETECTION_H
#define COLOR_DETECTION_H

#include <stdint.h>

#include "DEV_Config.h"

typedef struct {
    const char *name;
    UWORD r, g, b;
} Color;

extern const Color color_definitions[];
extern const size_t color_definitions_count;

// Function prototypes
const char *GetColorName(uint8_t r, uint8_t g, uint8_t b, float *confidence);

#endif

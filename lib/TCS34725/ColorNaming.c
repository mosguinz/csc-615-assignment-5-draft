#include <math.h>

#include "ColorNaming.h"

/* Define a list of predefined colors. */
const Color color_definitions[] = {
    {"Red", 255, 0, 0},
    {"Green", 0, 255, 0},
    {"Blue", 0, 0, 255},
    {"White", 255, 255, 255},
    {"Black", 0, 0, 0},
    {"Yellow", 255, 255, 0},
    {"Cyan", 0, 255, 255},
    {"Magenta", 255, 0, 255}
};

const size_t color_definitions_count = sizeof(color_definitions) / sizeof(color_definitions[0]);

/* Calculate Euclidean distance between two colors. */
static float CalculateColorDistance(uint8_t r1, uint8_t g1, uint8_t b1,
                                    uint8_t r2, uint8_t g2, uint8_t b2) {
    return sqrtf(powf(r1 - r2, 2) + powf(g1 - g2, 2) + powf(b1 - b2, 2));
}

/* Get color name and set "confidence" value. */
const char *GetColorName(uint8_t r, uint8_t g, uint8_t b, float *confidence) {
    float min_distance = INFINITY;
    const Color *closest_color = NULL;

    for (size_t i = 0; i < color_definitions_count; i++) {
        float distance = CalculateColorDistance(
          r, g, b,
          color_definitions[i].r,
          color_definitions[i].g,
          color_definitions[i].b
        );
        if (distance < min_distance) {
            min_distance = distance;
            closest_color = &color_definitions[i];
        }
    }

    /* Normalize the confidence value. */
    /* Max distance is approx. 441.67 = sqrt(255^2 + 255^2 + 255^2) */
    if (confidence != NULL) {
        *confidence = 1.0f - (min_distance / 441.67295593f);
    }

    return closest_color ? closest_color->name : "Unknown";
}

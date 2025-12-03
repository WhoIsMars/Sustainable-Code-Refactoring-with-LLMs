#include "resistor_color.h"

int color_code(resistor_band_t color)
{
    return color;
}

resistor_band_t *colors()
{
    static resistor_band_t list_colors[MAX_BANDS] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    static int initialized = 0;
    
    if (!initialized) {
        initialized = 1;
    }
    
    return list_colors;
}
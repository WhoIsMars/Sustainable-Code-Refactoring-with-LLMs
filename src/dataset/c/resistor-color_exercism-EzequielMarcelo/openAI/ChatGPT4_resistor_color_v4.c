#include "resistor_color.h"

int color_code(resistor_band_t color)
{
    return color;
}

resistor_band_t *colors()
{
    static resistor_band_t list_colors[MAX_BANDS] = { 
        [0 ... MAX_BANDS - 1] = 0 
    };

    return list_colors;
}
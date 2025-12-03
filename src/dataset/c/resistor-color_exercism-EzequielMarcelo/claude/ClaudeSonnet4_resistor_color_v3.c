#include "resistor_color.h"

int color_code(resistor_band_t color)
{
    return color;
}

resistor_band_t *colors()
{
    static resistor_band_t list_colors[MAX_BANDS] = {
        BLACK, BROWN, RED, ORANGE, YELLOW, GREEN, BLUE, VIOLET, GREY, WHITE
    };
    static int initialized = 0;
    
    if (!initialized) {
        for (int x = 0; x < MAX_BANDS; x++) {
            list_colors[x] = (resistor_band_t)x;
        }
        initialized = 1;
    }
    
    return list_colors;
}
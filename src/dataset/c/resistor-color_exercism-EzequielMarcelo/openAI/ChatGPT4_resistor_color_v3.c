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
    return list_colors;
}
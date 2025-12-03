#include "resistor_color.h"

int color_code(resistor_band_t color) 
{ 
    return (int)color;
}

static const resistor_band_t color_array[] = {
    BLACK, BROWN, RED, ORANGE, YELLOW, GREEN, BLUE, VIOLET, GREY, WHITE
};

const resistor_band_t *colors(void) { 
    return color_array; 
}
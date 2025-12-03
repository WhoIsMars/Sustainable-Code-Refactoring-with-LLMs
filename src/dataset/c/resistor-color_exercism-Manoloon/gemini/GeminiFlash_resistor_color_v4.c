#include "resistor_color.h"

int color_code(resistor_band_t color)
{
    return (int)color;
}

const resistor_band_t *colors(void)
{
    return (const resistor_band_t[]){BLACK, BROWN, RED, ORANGE, YELLOW, GREEN, BLUE, VIOLET, GREY, WHITE};
}
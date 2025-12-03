#include "resistor_color.h"

const resistor_band_t resistor_bands[] = {BLACK, BROWN, RED, ORANGE, YELLOW,
                                          GREEN, BLUE, VIOLET, GREY, WHITE};

resistor_band_t color_code(resistor_band_t code)
{
    return (code >= BLACK && code <= WHITE) ? code : BLACK;
}

const resistor_band_t *colors(void)
{
    return resistor_bands;
}
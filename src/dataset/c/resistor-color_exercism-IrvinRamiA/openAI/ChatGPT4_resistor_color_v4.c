#include "resistor_color.h"

const resistor_band_t *colors(void)
{
    static const resistor_band_t resistor_bands[] = {BLACK, BROWN, RED, ORANGE, YELLOW,
                                                     GREEN, BLUE, VIOLET, GREY, WHITE};
    return resistor_bands;
}

resistor_band_t color_code(resistor_band_t code)
{
    return (code >= BLACK && code <= WHITE) ? colors()[code] : BLACK;
}
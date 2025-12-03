#include "resistor_color.h"


resistor_band_t color_code(uint32_t color)
{
    return (resistor_band_t)color;
}


resistor_band_t *colors(void)
{
    resistor_band_t *clr = malloc(10 * sizeof(resistor_band_t));

    for (resistor_band_t i = 0; i <= WHITE; i++) {
        clr[i] = i;
    }

    return clr;
}

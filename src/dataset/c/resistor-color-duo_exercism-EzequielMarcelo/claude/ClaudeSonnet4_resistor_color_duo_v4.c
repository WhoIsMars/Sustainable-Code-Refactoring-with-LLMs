#include "resistor_color_duo.h"

uint16_t color_code(resistor_band_t *colors)
{
    return (colors[0] << 3) + (colors[0] << 1) + colors[1];
}
#include "resistor_color_duo.h"

unsigned short color_code(resistor_band_t resistor_band[])
{
    return (resistor_band[0] * 10) + resistor_band[1];
}
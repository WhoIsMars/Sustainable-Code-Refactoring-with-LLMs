#include "resistor_color_duo.h"

unsigned short color_code(const resistor_band_t resistor_band[])
{
    return (resistor_band[0] * 10U) + resistor_band[1];
}
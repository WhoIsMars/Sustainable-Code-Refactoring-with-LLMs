#include "resistor_color_duo.h"

inline uint16_t color_code(const resistor_band_t colors[])
{
    return (colors[0] * 10U) + colors[1];
}
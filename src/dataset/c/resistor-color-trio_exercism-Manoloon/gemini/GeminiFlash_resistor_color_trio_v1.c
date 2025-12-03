#include "resistor_color_trio.h"

resistor_value_t color_code(const resistor_band_t colors[3])
{
    resistor_value_t result;
    uint32_t raw_value = (colors[0] * 10 + colors[1]);
    uint32_t multiplier = 1;

    for (int i = 0; i < colors[2]; ++i) {
        if (multiplier > 1000000000 / 10) {
            result.unit = GIGAOHMS;
            result.value = (raw_value + 5) / 100;
            return result;
        }
        multiplier *= 10;
    }

    raw_value *= multiplier;

    if (raw_value >= 1000000000)
    {
        result.unit = GIGAOHMS;
        result.value = raw_value / 1000000000;
        return result;
    }
    if (raw_value >= 1000000)
    {
        result.unit = MEGAOHMS;
        result.value = raw_value / 1000000;
        return result;
    }
    if (raw_value >= 1000)
    {
        result.unit = KILOOHMS;
        result.value = raw_value / 1000;
        return result;
    }
    result.unit = OHMS;
    result.value = raw_value;
    return result;
}
#include "resistor_color_trio.h"

resistor_value_t color_code(const resistor_band_t colors[3])
{
    resistor_value_t result;
    int64_t raw_value = (colors[0] * 10 + colors[1]);
    int64_t multiplier = 1;

    for (int i = 0; i < colors[2]; ++i) {
        if (raw_value > INT64_MAX / 10) {
            result.unit = GIGAOHMS;
            result.value = 0;
            return result;
        }
        raw_value *= 10;
    }
    
    if (raw_value >= 1000000000) {
        result.unit = GIGAOHMS;
        result.value = raw_value / 1000000000;
    } else if (raw_value >= 1000000) {
        result.unit = MEGAOHMS;
        result.value = raw_value / 1000000;
    } else if (raw_value >= 1000) {
        result.unit = KILOOHMS;
        result.value = raw_value / 1000;
    } else {
        result.unit = OHMS;
        result.value = raw_value;
    }
    return result;
}
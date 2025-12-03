#include "resistor_color_trio.h"

resistor_value_t color_code(const resistor_band_t colors[3])
{
    resistor_value_t result;
    int64_t raw_value = (colors[0] * 10 + colors[1]);
    int64_t multiplier = 1;

    switch (colors[2]) {
        case BROWN:   multiplier = 10; break;
        case RED:     multiplier = 100; break;
        case ORANGE:  multiplier = 1000; break;
        case YELLOW:  multiplier = 10000; break;
        case GREEN:   multiplier = 100000; break;
        case BLUE:    multiplier = 1000000; break;
        case VIOLET:  multiplier = 10000000; break;
        case GREY:    multiplier = 100000000; break;
        case WHITE:   multiplier = 1000000000; break;
        default:      multiplier = 1; break; // BLACK or invalid
    }

    raw_value *= multiplier;

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
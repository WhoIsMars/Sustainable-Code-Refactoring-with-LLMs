#include "resistor_color_trio.h"

resistor_value_t color_code(const resistor_band_t colors[])
{
    resistor_value_t res;

    int base_value = (colors[0] * 10 + colors[1]);
    int multiplier = 1;
    for (int i = 0; i < colors[2]; i++) {
        multiplier *= 10;
    }
    res.value = base_value * multiplier;
    res.unit = OHMS;

    if (res.value >= 1000 && res.value % 1000 == 0) {
        res.unit = KILOOHMS;
        res.value /= 1000;
    }

    return res;
}
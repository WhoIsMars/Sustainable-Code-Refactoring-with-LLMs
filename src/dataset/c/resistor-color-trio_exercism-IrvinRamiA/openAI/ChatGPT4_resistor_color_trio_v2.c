#include "resistor_color_trio.h"

resistor_value_t color_code(resistor_band_t resistor_band[])
{
    resistor_value_t resistor_value;

    int multiplier = 1;
    for (int i = 0; i < resistor_band[2]; i++) {
        multiplier *= 10;
    }

    resistor_value.value = (resistor_band[0] * 10 + resistor_band[1]) * multiplier;

    if (resistor_value.value >= 1000)
    {
        resistor_value.value /= 1000;
        resistor_value.unit = KILOOHMS;
    }
    else
    {
        resistor_value.unit = OHMS;
    }

    return resistor_value;
}
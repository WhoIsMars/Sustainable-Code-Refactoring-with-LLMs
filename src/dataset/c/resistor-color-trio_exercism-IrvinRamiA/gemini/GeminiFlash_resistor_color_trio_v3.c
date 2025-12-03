#include "resistor_color_trio.h"
#include <stdio.h>

resistor_value_t color_code(resistor_band_t resistor_band[])
{
    resistor_value_t resistor_value;
    unsigned int value = (resistor_band[0] * 10 + resistor_band[1]);

    if (resistor_band[2] == 0) {
        // No multiplier needed
    } else if (resistor_band[2] == 1) {
        value *= 10;
    } else if (resistor_band[2] == 2) {
        value *= 100;
    } else if (resistor_band[2] == 3) {
        value *= 1000;
    } else if (resistor_band[2] == 4) {
        value *= 10000;
    } else if (resistor_band[2] == 5) {
        value *= 100000;
    } else if (resistor_band[2] == 6) {
        value *= 1000000;
    } else {
        value = 0; // Handle invalid multiplier (optional)
    }

    resistor_value.value = value;

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
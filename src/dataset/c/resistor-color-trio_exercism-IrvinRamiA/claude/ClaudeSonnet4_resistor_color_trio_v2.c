#include "resistor_color_trio.h"

resistor_value_t color_code(resistor_band_t resistor_band[])
{
    resistor_value_t resistor_value;
    
    resistor_value.value = (resistor_band[0] * 10 + resistor_band[1]);
    
    // Use bit shifting and multiplication instead of pow() for powers of 10
    int multiplier = resistor_band[2];
    while (multiplier > 0) {
        resistor_value.value *= 10;
        multiplier--;
    }

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
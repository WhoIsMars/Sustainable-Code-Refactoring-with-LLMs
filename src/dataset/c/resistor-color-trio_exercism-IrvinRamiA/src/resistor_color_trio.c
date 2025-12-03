#include "resistor_color_trio.h"
#include <math.h>
#include <stdio.h>

resistor_value_t color_code(resistor_band_t resistor_band[])
{
    resistor_value_t resistor_value;
    
    resistor_value.value = (resistor_band[0] * 10 + resistor_band[1]);
    resistor_value.value *= pow(10, resistor_band[2]);

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

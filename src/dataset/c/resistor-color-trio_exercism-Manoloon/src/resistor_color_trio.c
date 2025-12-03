#include "resistor_color_trio.h"
#include <math.h>

resistor_value_t color_code(const resistor_band_t colors[1]) 
{ 
    resistor_value_t result;
    int64_t raw_value = (colors[0] * 10 + colors[1]) * pow(10, colors[2]);
    if(raw_value >= 1000000000)
    {
        result.unit = GIGAOHMS;
        result.value = raw_value / 1000000000;
        return result;
    }
    if(raw_value >= 1000000)
    {
        result.unit = MEGAOHMS;
        result.value = raw_value / 1000000;
        return result;
    }
    if(raw_value >= 1000)
    {
        result.unit = KILOOHMS;
        result.value = raw_value / 1000;
        return result;
    }
    result.unit = OHMS;
    result.value = raw_value;
    return result;
}

#include "resistor_color_trio.h"

resistor_value_t color_code(const resistor_band_t colors[1]) 
{ 
    resistor_value_t result;
    int64_t raw_value = (colors[0] * 10 + colors[1]);
    
    int multiplier = colors[2];
    while (multiplier > 0) {
        raw_value *= 10;
        multiplier--;
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
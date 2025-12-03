#include "resistor_color_trio.h"

resistor_value_t color_code(const resistor_band_t colors[1]) 
{ 
    resistor_value_t result;
    int64_t base_value = colors[0] * 10 + colors[1];
    
    if (colors[2] >= 9) {
        result.unit = GIGAOHMS;
        result.value = base_value;
        if (colors[2] > 9) {
            int64_t multiplier = 1;
            for (int i = 9; i < colors[2]; i++) {
                multiplier *= 10;
            }
            result.value *= multiplier;
        }
        return result;
    }
    
    if (colors[2] >= 6) {
        result.unit = MEGAOHMS;
        result.value = base_value;
        for (int i = 6; i < colors[2]; i++) {
            result.value *= 10;
        }
        return result;
    }
    
    if (colors[2] >= 3) {
        result.unit = KILOOHMS;
        result.value = base_value;
        for (int i = 3; i < colors[2]; i++) {
            result.value *= 10;
        }
        return result;
    }
    
    result.unit = OHMS;
    result.value = base_value;
    for (int i = 0; i < colors[2]; i++) {
        result.value *= 10;
    }
    return result;
}
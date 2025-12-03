#include "resistor_color_trio.h"

resistor_value_t color_code(resistor_band_t resistor_band[])
{
    resistor_value_t resistor_value;
    
    resistor_value.value = resistor_band[0] * 10 + resistor_band[1];
    
    if (resistor_band[2] == 0) {
        resistor_value.unit = OHMS;
    } else if (resistor_band[2] == 1) {
        resistor_value.value *= 10;
        resistor_value.unit = OHMS;
    } else if (resistor_band[2] == 2) {
        resistor_value.value *= 100;
        resistor_value.unit = OHMS;
    } else if (resistor_band[2] == 3) {
        resistor_value.unit = KILOOHMS;
    } else if (resistor_band[2] == 4) {
        resistor_value.value *= 10;
        resistor_value.unit = KILOOHMS;
    } else if (resistor_band[2] == 5) {
        resistor_value.value *= 100;
        resistor_value.unit = KILOOHMS;
    } else {
        int multiplier = 1;
        for (int i = 0; i < resistor_band[2]; i++) {
            multiplier *= 10;
        }
        resistor_value.value *= multiplier;
        
        if (resistor_value.value >= 1000) {
            resistor_value.value /= 1000;
            resistor_value.unit = KILOOHMS;
        } else {
            resistor_value.unit = OHMS;
        }
    }
    
    return resistor_value;
}
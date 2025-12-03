#include "resistor_color_trio.h"

static const int powers_of_10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

resistor_value_t color_code(const resistor_band_t colors[])
{
    resistor_value_t res;
    
    int base_value = colors[0] * 10 + colors[1];
    int multiplier_index = colors[2];
    
    if (multiplier_index < 10) {
        res.value = base_value * powers_of_10[multiplier_index];
    } else {
        res.value = base_value;
        for (int i = 0; i < multiplier_index; i++) {
            res.value *= 10;
        }
    }
    
    if (res.value >= 1000 && res.value % 1000 == 0) {
        res.unit = KILOOHMS;
        res.value /= 1000;
    } else {
        res.unit = OHMS;
    }
    
    return res;
}
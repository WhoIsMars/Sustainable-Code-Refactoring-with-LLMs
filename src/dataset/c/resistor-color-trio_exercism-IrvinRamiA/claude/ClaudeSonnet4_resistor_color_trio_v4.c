#include "resistor_color_trio.h"

static const int power_of_ten[] = {
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000
};

resistor_value_t color_code(resistor_band_t resistor_band[])
{
    resistor_value_t resistor_value;
    
    int base_value = resistor_band[0] * 10 + resistor_band[1];
    int multiplier_index = resistor_band[2];
    
    if (multiplier_index < 10) {
        resistor_value.value = base_value * power_of_ten[multiplier_index];
    } else {
        resistor_value.value = base_value;
    }

    if (resistor_value.value >= 1000) {
        resistor_value.value /= 1000;
        resistor_value.unit = KILOOHMS;
    } else {
        resistor_value.unit = OHMS;
    }
    
    return resistor_value;
}
#include "resistor_color_trio.h"

resistor_value_t color_code(const resistor_band_t colors[1]) 
{ 
    resistor_value_t result;
    int64_t raw_value = (colors[0] * 10 + colors[1]);
    
    // Use bit shifting and multiplication instead of pow() for powers of 10
    switch(colors[2]) {
        case 0: break;
        case 1: raw_value *= 10; break;
        case 2: raw_value *= 100; break;
        case 3: raw_value *= 1000; break;
        case 4: raw_value *= 10000; break;
        case 5: raw_value *= 100000; break;
        case 6: raw_value *= 1000000; break;
        case 7: raw_value *= 10000000; break;
        case 8: raw_value *= 100000000; break;
        case 9: raw_value *= 1000000000; break;
        default: 
            // For larger powers, use multiplication loop
            for(int i = 0; i < colors[2]; i++) {
                raw_value *= 10;
            }
    }
    
    if(raw_value >= 1000000000) {
        result.unit = GIGAOHMS;
        result.value = raw_value / 1000000000;
    } else if(raw_value >= 1000000) {
        result.unit = MEGAOHMS;
        result.value = raw_value / 1000000;
    } else if(raw_value >= 1000) {
        result.unit = KILOOHMS;
        result.value = raw_value / 1000;
    } else {
        result.unit = OHMS;
        result.value = raw_value;
    }
    
    return result;
}
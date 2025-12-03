#include "resistor_color_duo.h"
#include <stdint.h>

uint16_t color_code(const resistor_band_t *resis_band){
    static const uint8_t color_values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    uint8_t first_digit = 0;
    uint8_t second_digit = 0;
    
    if (resis_band[0] >= BLACK && resis_band[0] <= WHITE) {
        first_digit = color_values[resis_band[0]];
    }
    
    if (resis_band[1] >= BLACK && resis_band[1] <= WHITE) {
        second_digit = color_values[resis_band[1]];
    }
    
    return first_digit * 10 + second_digit;
}
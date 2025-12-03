#include "resistor_color_duo.h"
#include <stdint.h>

uint16_t color_code(const resistor_band_t *resis_band){
    uint16_t first_digit = (uint16_t)resis_band[0];
    uint16_t second_digit = (uint16_t)resis_band[1];
    
    return first_digit * 10 + second_digit;
}
#include "resistor_color_duo.h"
#include <stdint.h>

uint16_t color_code(const resistor_band_t *resis_band){
    return (uint16_t)resis_band[0] * 10 + (uint16_t)resis_band[1];
}
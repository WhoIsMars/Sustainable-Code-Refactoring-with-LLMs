#include "resistor_color_duo.h"

uint16_t color_code(const resistor_band_t* c) {
    return c[0] * 10 + c[1];
}
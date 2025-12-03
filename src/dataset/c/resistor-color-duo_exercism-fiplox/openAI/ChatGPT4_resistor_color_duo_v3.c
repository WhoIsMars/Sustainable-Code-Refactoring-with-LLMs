#include "resistor_color_duo.h"

uint16_t color_code(resistor_band_t* c) {
	return (uint16_t)(c[0] * 10 + c[1]);
}
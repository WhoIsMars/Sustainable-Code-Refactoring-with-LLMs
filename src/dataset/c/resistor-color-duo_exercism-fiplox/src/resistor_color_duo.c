#include "resistor_color_duo.h"

uint16_t color_code(resistor_band_t* c) {
	uint16_t res;
	res = 0;

	res = c[0];
	res *= 10;
	res += c[1];

	return res;
}
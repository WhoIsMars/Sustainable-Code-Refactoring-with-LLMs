#include "resistor_color_trio.h"

resistor_value_t color_code(const resistor_band_t colors[])
{
	resistor_value_t res;
	
	// Use bit shifting and multiplication instead of pow() for powers of 10
	int base_value = colors[0] * 10 + colors[1];
	int multiplier = colors[2];
	
	// Calculate power of 10 using lookup table for small values or iterative multiplication
	if (multiplier <= 9) {
		static const int pow10_table[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
		res.value = base_value * pow10_table[multiplier];
	} else {
		res.value = base_value;
		for (int i = 0; i < multiplier; i++) {
			res.value *= 10;
		}
	}
	
	// Check for kiloohms conversion
	if (res.value >= 1000 && (res.value % 1000) == 0) {
		res.unit = KILOOHMS;
		res.value /= 1000;
	} else {
		res.unit = OHMS;
	}
	
	return res;
}
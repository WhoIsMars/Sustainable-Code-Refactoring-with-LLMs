#include "resistor_color_trio.h"

resistor_value_t color_code(const resistor_band_t colors[])
{
	resistor_value_t res;
	
	int base_value = colors[0] * 10 + colors[1];
	
	if (colors[2] >= 3) {
		int kiloohm_multiplier = colors[2] - 3;
		res.value = base_value;
		for (int i = 0; i < kiloohm_multiplier; ++i) {
			res.value *= 10;
		}
		res.unit = KILOOHMS;
	} else {
		res.value = base_value;
		for (int i = 0; i < colors[2]; ++i) {
			res.value *= 10;
		}
		res.unit = OHMS;
	}
	
	return res;
}
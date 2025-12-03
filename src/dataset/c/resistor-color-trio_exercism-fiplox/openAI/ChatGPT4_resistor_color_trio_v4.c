#include "resistor_color_trio.h"

resistor_value_t color_code(const resistor_band_t colors[])
{
	resistor_value_t res;

	int base_value = colors[0] * 10 + colors[1];
	for (int i = 0; i < colors[2]; i++) {
		base_value *= 10;
	}

	res.value = base_value;
	res.unit = OHMS;

	if (base_value >= 1000) {
		res.unit = KILOOHMS;
		res.value = base_value / 1000;
	}

	return res;
}
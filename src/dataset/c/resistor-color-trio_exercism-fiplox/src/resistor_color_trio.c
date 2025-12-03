#include "resistor_color_trio.h"
#include <math.h>

resistor_value_t color_code(const resistor_band_t colors[])
{
	resistor_value_t res;

	res.value = (colors[0] * 10 + colors[1]) * pow(10, colors[2]);
	res.unit = OHMS;

	if ((res.value % 1000) == 0) {
		res.unit = KILOOHMS;
		res.value /= 1000;
	}

	return res;
}
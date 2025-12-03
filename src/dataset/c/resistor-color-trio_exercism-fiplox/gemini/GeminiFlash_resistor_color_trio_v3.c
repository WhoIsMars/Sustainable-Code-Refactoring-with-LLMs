#include "resistor_color_trio.h"

resistor_value_t color_code(const resistor_band_t colors[])
{
	resistor_value_t res;

	res.value = (colors[0] * 10 + colors[1]);

	switch (colors[2]) {
		case BLACK:
			break;
		case BROWN:
			res.value *= 10;
			break;
		case RED:
			res.value *= 100;
			break;
		case ORANGE:
			res.value *= 1000;
			break;
		case YELLOW:
			res.value *= 10000;
			break;
		case GREEN:
			res.value *= 100000;
			break;
		case BLUE:
			res.value *= 1000000;
			break;
		case VIOLET:
			res.value *= 10000000;
			break;
		case GREY:
			res.value *= 100000000;
			break;
		case WHITE:
			res.value *= 1000000000;
			break;
	}

	res.unit = OHMS;

	if (res.value >= 1000 && (res.value % 1000) == 0) {
		res.unit = KILOOHMS;
		res.value /= 1000;
	}

	return res;
}
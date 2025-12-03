#include "darts.h"

#include <math.h>

uint8_t score(coordinate_t c)
{
	float r;

	r = sqrtf(c.x * c.x + c.y * c.y);

	if (r <= 1) {
		return 10;
	}
	if (r <= 5) {
		return 5;
	}
	if (r <= 10) {
		return 1;
	}

	return 0;
}
#include "darts.h"

#include <math.h>

uint8_t score(coordinate_t c)
{
    float r2 = c.x * c.x + c.y * c.y;

    if (r2 <= 1.0f) {
        return 10;
    }
    if (r2 <= 25.0f) {
        return 5;
    }
    if (r2 <= 100.0f) {
        return 1;
    }

    return 0;
}
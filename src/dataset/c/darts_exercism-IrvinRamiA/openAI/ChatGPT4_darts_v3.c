#include "darts.h"
#include <math.h>

uint8_t score(coordinate_t landing_position)
{
    double vector_magnitude_squared = landing_position.x * landing_position.x +
                                      landing_position.y * landing_position.y;

    if (vector_magnitude_squared <= 1.0)
    {
        return 10;
    }
    else if (vector_magnitude_squared <= 25.0)
    {
        return 5;
    }
    else if (vector_magnitude_squared <= 100.0)
    {
        return 1;
    }

    return 0;
}
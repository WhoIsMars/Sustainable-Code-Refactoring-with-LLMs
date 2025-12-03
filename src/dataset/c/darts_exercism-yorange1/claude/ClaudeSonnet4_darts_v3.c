#include "darts.h"

#include <math.h>

#define INNER_CIRCLE_RADIUS_SQUARED (1.0f)
#define MIDDLE_CIRCLE_RADIUS_SQUARED (25.0f)
#define OUTER_CIRCLE_RADIUS_SQUARED (100.0f)

uint8_t score(coordinate_t landing_position)
{
    const float dist_squared = landing_position.x * landing_position.x + landing_position.y * landing_position.y;

    if (dist_squared <= INNER_CIRCLE_RADIUS_SQUARED)
    {
        return 10;
    }
    else if (dist_squared <= MIDDLE_CIRCLE_RADIUS_SQUARED)
    {
        return 5;
    }
    else if (dist_squared <= OUTER_CIRCLE_RADIUS_SQUARED)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
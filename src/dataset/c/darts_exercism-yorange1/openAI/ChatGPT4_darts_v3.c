#include "darts.h"

#include <math.h>

#define INNER_CIRCLE_RADIUS_SQ (1.0f * 1.0f)
#define MIDDLE_CIRCLE_RADIUS_SQ (5.0f * 5.0f)
#define OUTER_CIRCLE_RADIUS_SQ (10.0f * 10.0f)

uint8_t score(coordinate_t landing_position)
{
    float dist_sq = landing_position.x * landing_position.x + landing_position.y * landing_position.y;

    if (dist_sq <= INNER_CIRCLE_RADIUS_SQ)
    {
        return 10;
    }
    if (dist_sq <= MIDDLE_CIRCLE_RADIUS_SQ)
    {
        return 5;
    }
    if (dist_sq <= OUTER_CIRCLE_RADIUS_SQ)
    {
        return 1;
    }
    return 0;
}
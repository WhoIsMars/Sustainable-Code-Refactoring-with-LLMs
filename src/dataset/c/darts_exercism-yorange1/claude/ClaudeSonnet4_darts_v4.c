#include "darts.h"

#define INNER_CIRCLE_RADIUS_SQ (1.0f)
#define MIDDLE_CIRCLE_RADIUS_SQ (25.0f)
#define OUTER_CIRCLE_RADIUS_SQ (100.0f)

uint8_t score(coordinate_t landing_position)
{
    const float dist_sq = landing_position.x * landing_position.x + landing_position.y * landing_position.y;

    if (dist_sq <= INNER_CIRCLE_RADIUS_SQ)
    {
        return 10;
    }
    else if (dist_sq <= MIDDLE_CIRCLE_RADIUS_SQ)
    {
        return 5;
    }
    else if (dist_sq <= OUTER_CIRCLE_RADIUS_SQ)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
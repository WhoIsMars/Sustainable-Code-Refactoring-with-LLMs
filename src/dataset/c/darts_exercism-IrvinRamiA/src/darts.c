#include "darts.h"
#include <math.h>

/**
 * @brief This function returns the earned points in a single toss of a Darts game.
 *
 * @param landing_position
 * @return uint8_t
 *
 * outher circle radius = 10 units
 * middle circle radius = 5 units
 * inner circle radius = 1 unit
 *
 * Points:
 * If the dart lands outside the target, player earns no points (0 points).
 * If the dart lands in the outer circle of the target, player earns 1 point.
 * If the dart lands in the middle circle of the target, player earns 5 points.
 * If the dart lands in the inner circle of the target, player earns 10 points.
 */

uint8_t score(coordinate_t landing_position)
{
    uint8_t score = 0;

    double vector_magnitude = sqrt(landing_position.x * landing_position.x +
                                   landing_position.y * landing_position.y);

    if(vector_magnitude <= 1.0)
    {
        score += 10;
    }
    else if(vector_magnitude <= 5.0)
    {
        score += 5;
    }
    else if(vector_magnitude <= 10.0)
    {
        score += 1;
    }

    return score;
}

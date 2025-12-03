#include "darts.h"

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
    double distance_squared = landing_position.x * landing_position.x +
                             landing_position.y * landing_position.y;

    if(distance_squared <= 1.0)
    {
        return 10;
    }
    else if(distance_squared <= 25.0)
    {
        return 5;
    }
    else if(distance_squared <= 100.0)
    {
        return 1;
    }

    return 0;
}
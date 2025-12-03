#include "darts.h"

uint8_t score(coordinate_t landing_position)
{
    double distance_squared = landing_position.x * landing_position.x +
                              landing_position.y * landing_position.y;

    if (distance_squared <= 1.0)
    {
        return 10;
    }
    else if (distance_squared <= 25.0)
    {
        return 5;
    }
    else if (distance_squared <= 100.0)
    {
        return 1;
    }

    return 0;
}
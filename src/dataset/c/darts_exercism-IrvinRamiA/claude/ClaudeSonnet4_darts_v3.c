#include "darts.h"

uint8_t score(coordinate_t landing_position)
{
    const double x_squared = landing_position.x * landing_position.x;
    const double y_squared = landing_position.y * landing_position.y;
    const double distance_squared = x_squared + y_squared;

    if (distance_squared <= 1.0) {
        return 10;
    }
    if (distance_squared <= 25.0) {
        return 5;
    }
    if (distance_squared <= 100.0) {
        return 1;
    }
    
    return 0;
}
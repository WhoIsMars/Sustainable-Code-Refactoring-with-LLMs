#include "darts.h"
#include <math.h>

uint8_t score(coordinate_t landing_position)
{
    double x = landing_position.x;
    double y = landing_position.y;
    double distance_squared = x * x + y * y;

    if (distance_squared <= 1.0) {
        return 10;
    } else if (distance_squared <= 25.0) {
        return 5;
    } else if (distance_squared <= 100.0) {
        return 1;
    } else {
        return 0;
    }
}
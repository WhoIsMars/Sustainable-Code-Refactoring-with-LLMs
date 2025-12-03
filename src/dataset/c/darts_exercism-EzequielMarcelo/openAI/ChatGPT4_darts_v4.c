#include "darts.h"

uint8_t score(coordinate_t coordinate) 
{
    float x2 = coordinate.x * coordinate.x;
    float y2 = coordinate.y * coordinate.y;
    float distance_squared = x2 + y2;

    if (distance_squared > 100.0f) 
        return 0; 
    else if (distance_squared <= 1.0f) 
        return 10; 
    else if (distance_squared <= 25.0f) 
        return 5; 
    else 
        return 1;
}
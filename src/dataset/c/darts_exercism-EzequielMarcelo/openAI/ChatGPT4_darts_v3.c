#include "darts.h"

uint8_t score(coordinate_t coordinate) 
{
    float x2_y2 = coordinate.x * coordinate.x + coordinate.y * coordinate.y;

    if (x2_y2 > 100.0f) 
        return 0; 
    else if (x2_y2 <= 1.0f) 
        return 10; 
    else if (x2_y2 <= 25.0f) 
        return 5; 
    else 
        return 1;
}
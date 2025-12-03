#include "darts.h"

uint8_t score(coordinate_t coordinate) 
{
    float distance = sqrt(pow(coordinate.x, 2) + pow(coordinate.y, 2));

    if (distance > 10.0) 
        return 0; 
    else if (distance <= 1.0) 
        return 10; 
    else if (distance <= 5.0) 
        return 5; 
    else 
        return 1;
}
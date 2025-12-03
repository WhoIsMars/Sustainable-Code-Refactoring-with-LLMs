#include "darts.h"
#include <math.h>
#include <stdint.h>

uint8_t score(coordinate_t landing_position){
    coordinate_t dart_land = landing_position;
    float target_area = (pow(dart_land.x, 2) + pow(dart_land.y, 2));//(x)2 + (y)2
    
    uint8_t point = 0 ;
    if (target_area > 100)  point += 0;//out of target
    else if ((target_area <= 100) && (target_area > 25)) point += 1; // outer circle
    else if ((target_area <= 25) && (target_area > 1)) point += 5;//middle circle
    else point += 10; //inner circle

    return point;
    
}
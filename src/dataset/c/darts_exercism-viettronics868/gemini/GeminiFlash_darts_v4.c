#include "darts.h"
#include <math.h>
#include <stdint.h>

uint8_t score(coordinate_t landing_position){
    float distance_squared = (landing_position.x * landing_position.x) + (landing_position.y * landing_position.y);
    
    if (distance_squared > 100) {
        return 0;
    } else if (distance_squared > 25) {
        return 1;
    } else if (distance_squared > 1) {
        return 5;
    } else {
        return 10;
    }
}
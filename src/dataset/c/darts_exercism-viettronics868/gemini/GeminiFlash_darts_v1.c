#include "darts.h"
#include <math.h>
#include <stdint.h>

uint8_t score(coordinate_t landing_position){
    float target_area = (landing_position.x * landing_position.x) + (landing_position.y * landing_position.y);
    
    if (target_area > 100) {
        return 0;
    } else if (target_area > 25) {
        return 1;
    } else if (target_area > 1) {
        return 5;
    } else {
        return 10;
    }
}
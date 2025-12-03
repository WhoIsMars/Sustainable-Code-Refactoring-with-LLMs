#include "darts.h"
#include <stdint.h>

uint8_t score(coordinate_t landing_position){
    float target_area = landing_position.x * landing_position.x + landing_position.y * landing_position.y;
    
    if (target_area > 100.0f) return 0;
    if (target_area > 25.0f) return 1;
    if (target_area > 1.0f) return 5;
    return 10;
}
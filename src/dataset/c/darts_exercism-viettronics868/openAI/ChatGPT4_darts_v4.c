#include "darts.h"
#include <stdint.h>

uint8_t score(coordinate_t landing_position) {
    float target_area = landing_position.x * landing_position.x + landing_position.y * landing_position.y;

    if (target_area > 100) return 0;       // out of target
    if (target_area > 25) return 1;        // outer circle
    if (target_area > 1) return 5;         // middle circle
    return 10;                             // inner circle
}
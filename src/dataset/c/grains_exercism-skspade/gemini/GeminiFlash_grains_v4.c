#include "grains.h"
#include <stdint.h>

#define BOARD_SIZE 64
#define FIRST_SQUARE 1

uint64_t square(uint8_t index) {
    if (index < FIRST_SQUARE || index > BOARD_SIZE) {
        return 0;
    }
    return ((uint64_t)1) << (index - 1);
}

uint64_t total(void) {
    return ((uint64_t)1 << BOARD_SIZE) - 1;
}
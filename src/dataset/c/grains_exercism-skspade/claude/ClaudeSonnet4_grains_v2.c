#include "grains.h"

#include <stddef.h>

#define BOARD_SIZE 64
#define FIRST_SQUARE 1

uint64_t square(uint8_t index)
{
    if (index < 1 || index > BOARD_SIZE)
    {
        return 0;
    }
    return 1ULL << (index - 1);
}

uint64_t total(void)
{
    return (1ULL << BOARD_SIZE) - 1;
}
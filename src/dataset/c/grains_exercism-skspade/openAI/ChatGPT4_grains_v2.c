#include "grains.h"

#include <stddef.h>
#include <stdint.h>

#define BOARD_SIZE 64

static uint64_t squares[BOARD_SIZE] = {0};
static uint8_t is_initialized = 0;

static void initialize_chessboard(void)
{
    squares[0] = 1;
    for (uint8_t i = 1; i < BOARD_SIZE; ++i)
    {
        squares[i] = squares[i - 1] << 1; // Use bit-shifting for efficiency
    }
    is_initialized = 1;
}

uint64_t square(uint8_t index)
{
    if (index < 1 || index > BOARD_SIZE)
    {
        return 0; // Error handling for invalid index
    }
    if (!is_initialized)
    {
        initialize_chessboard();
    }
    return squares[index - 1];
}

uint64_t total(void)
{
    if (!is_initialized)
    {
        initialize_chessboard();
    }
    return (uint64_t)((1ULL << BOARD_SIZE) - 1); // Use formula for sum of geometric series
}
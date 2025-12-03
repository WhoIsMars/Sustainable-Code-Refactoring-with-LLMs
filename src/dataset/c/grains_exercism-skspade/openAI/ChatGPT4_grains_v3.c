#include "grains.h"

#include <stddef.h>
#include <stdint.h>

#define BOARD_SIZE 64

static uint64_t squares[BOARD_SIZE] = {0};
static uint64_t total_grains = 0;
static int initialized = 0;

static void initialize_chessboard(void)
{
    squares[0] = 1;
    total_grains = 1;
    for (uint8_t i = 1; i < BOARD_SIZE; ++i)
    {
        squares[i] = squares[i - 1] << 1;
        total_grains += squares[i];
    }
    initialized = 1;
}

uint64_t square(uint8_t index)
{
    if (index < 1 || index > BOARD_SIZE)
    {
        return 0;
    }
    if (!initialized)
    {
        initialize_chessboard();
    }
    return squares[index - 1];
}

uint64_t total(void)
{
    if (!initialized)
    {
        initialize_chessboard();
    }
    return total_grains;
}
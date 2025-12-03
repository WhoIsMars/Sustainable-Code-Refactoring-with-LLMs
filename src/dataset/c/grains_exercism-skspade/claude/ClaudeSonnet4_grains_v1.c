#include "grains.h"

#include <stddef.h>

#define BOARD_SIZE 64
#define FIRST_SQUARE 1

static uint64_t squares[BOARD_SIZE] = {0};
static int initialized = 0;

uint64_t* create_and_populate_chessboard(void)
{
    if (!initialized) {
        squares[0] = 1;
        for (uint8_t i = 1; i < BOARD_SIZE; ++i) {
            squares[i] = squares[i - 1] << 1;
        }
        initialized = 1;
    }
    return squares;
}

uint64_t square(uint8_t index)
{
    if (index < 1 || index > BOARD_SIZE) {
        return 0;
    }
    
    if (!initialized) {
        create_and_populate_chessboard();
    }
    
    return squares[index - 1];
}

uint64_t total(void)
{
    if (!initialized) {
        create_and_populate_chessboard();
    }
    
    return UINT64_MAX;
}
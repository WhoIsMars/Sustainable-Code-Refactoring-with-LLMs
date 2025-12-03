#include "grains.h"

uint64_t square(uint8_t index)
{
	return index == 0 ? 0 : (uint64_t)1 << (index - 1);
}

uint64_t total(void)
{
	return UINT64_MAX; // Sum of all squares on a chessboard is 2^64 - 1
}
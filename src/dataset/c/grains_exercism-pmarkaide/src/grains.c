#include "grains.h"

uint64_t square(uint8_t index)
{
	uint64_t g = 1;
	for(int i = 2; i <= index; i++)
		g = g*2;
	return index == 0 ? 0 : g;
}

uint64_t total(void)
{
	uint64_t t = 1;
	for(int i = 2; i <= 64; i++)
		t += square(i);
	return t;
}
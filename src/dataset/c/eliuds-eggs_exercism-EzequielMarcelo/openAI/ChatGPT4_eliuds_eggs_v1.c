#include "eliuds_eggs.h"

unsigned int egg_count(unsigned int n)
{
    return __builtin_popcount(n);
}
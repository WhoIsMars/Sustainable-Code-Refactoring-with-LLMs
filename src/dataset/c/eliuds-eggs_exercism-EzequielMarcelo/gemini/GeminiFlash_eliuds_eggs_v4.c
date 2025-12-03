#include "eliuds_eggs.h"

unsigned int egg_count(unsigned int n)
{
    unsigned int count = 0;
    while (n) {
        n &= (n - 1);
        count++;
    }
    return count;
}
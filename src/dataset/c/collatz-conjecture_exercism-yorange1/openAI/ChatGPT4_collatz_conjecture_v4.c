#include "collatz_conjecture.h"

#define IS_EVEN(n) (!((n) & 1))

int steps(int start)
{
    if (start <= 0)
    {
        return ERROR_VALUE;
    }

    int count = 0;

    while (start != 1)
    {
        start = IS_EVEN(start) ? (start >> 1) : (start * 3 + 1);
        count++;
    }

    return count;
}
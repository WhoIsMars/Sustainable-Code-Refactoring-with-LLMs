#include "collatz_conjecture.h"

#define is_even(n) (((n) & 1) == 0)

int steps(int start)
{
    if (start <= 0)
    {
        return ERROR_VALUE;
    }

    int count = 0;

    while (start != 1)
    {
        start = is_even(start) ? (start >> 1) : (start * 3 + 1);
        count++;
    }

    return count;
}
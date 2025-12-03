#include "collatz_conjecture.h"

int steps(int start)
{
    if(start <= 0)
    {
        return ERROR_VALUE;
    }

    int count = 0;
    unsigned int n = (unsigned int)start;

    while (n > 1)
    {
        if (n & 1)
        {
            n = n * 3 + 1;
        }
        else
        {
            n >>= 1;
        }
        count++;
    }

    return count;
}
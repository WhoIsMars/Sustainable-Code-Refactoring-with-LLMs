#include "armstrong_numbers.h"
#include <math.h>

bool is_armstrong_number(int candidate)
{
    int num_digits = (int)(log10(candidate) + 1);
    int res = 0;
    int num = candidate;

    while (num > 0)
    {
        int digit = num % 10;
        res += pow(digit, num_digits);
        num = num / 10;
    }

    if (res == candidate)
        return true;
    else
        return false;
}

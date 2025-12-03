#include "nth_prime.h"
#include <stdbool.h>
#include <math.h>

#define U32_MAX_VALUE 4294967295

static bool is_prime(uint32_t number)
{
    if (number <= 1) return false;
    if (number <= 3) return true;
    if (number % 2 == 0 || number % 3 == 0) return false;

    uint32_t limit = sqrt(number);
    for (uint32_t i = 5; i <= limit; i += 6)
    {
        if (number % i == 0 || number % (i + 2) == 0)
        {
            return false;
        }
    }
    return true;
}

uint32_t nth(uint32_t n)
{
    if (n == 0) return 0;

    uint32_t count = 0;
    uint32_t candidate = 1;

    while (count < n)
    {
        candidate++;
        if (is_prime(candidate))
        {
            count++;
        }
    }

    return candidate;
}
#include "nth_prime.h"
#include <stdbool.h>

#define U32_MAX_VALUE 4294967295

static bool is_prime(uint32_t number)
{
    bool result = true;

    if (number == 2 || number == 3)
    {
        /* is prime */
    }
    else if (number <= 1 || number % 2 == 0 || number % 3 == 0)
    {
        result = false;
    }
    else
    {
        for (uint32_t i = 5; i * i <= number; i += 6)
        {
            if (number % i == 0 || number % (i + 2) == 0)
            {
                result = false;
            }
        }
    }

    return result;
}

uint32_t nth(uint32_t n)
{
    uint32_t nth_prime = 0;

    if (n == 0)
    {
        nth_prime = 0;
    }
    else
    {
        uint32_t primes_counter = 0;

        for (uint32_t i = 2;; i++)
        {
            if (is_prime(i))
            {
                primes_counter++;
            }

            if (primes_counter == n)
            {
                nth_prime = i;
                break;
            }
        }
    }

    return nth_prime;
}

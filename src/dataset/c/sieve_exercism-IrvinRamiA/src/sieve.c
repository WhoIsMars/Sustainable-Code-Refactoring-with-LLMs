#include "sieve.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

uint32_t sieve(uint32_t limit, uint32_t *primes, size_t max_primes)
{
    unsigned int primes_counter = 0;
    bool *is_prime = (bool *)calloc(limit + 1, sizeof(bool));

    memset(is_prime, true, (limit + 1) * sizeof(bool));

    for (unsigned int i = 2; i * i <= limit; i++)
    {
        if (*(is_prime + i) == true)
        {
            for (unsigned int j = i * i; j <= limit; j += i)
            {
                *(is_prime + j) = false;
            }
        }
    }

    for (unsigned int i = 2; i <= limit; i++)
    {
        if ((*(is_prime + i) == true) && (primes_counter < max_primes))
        {
            primes[primes_counter++] = i;
        }
    }

    return primes_counter;
}

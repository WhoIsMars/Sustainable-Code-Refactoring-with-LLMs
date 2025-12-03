#include "sum_of_multiples.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

unsigned int sum(const unsigned int *factors, const size_t number_of_factors,
                 const unsigned int limit)
{
    if (limit == 0 || number_of_factors == 0)
        return 0;

    bool *bitmap = (bool *)calloc(limit, sizeof(bool));
    if (!bitmap)
        return 0;

    unsigned int result = 0;

    for (size_t i = 0; i < number_of_factors; i++)
    {
        unsigned int factor = factors[i];
        if (factor == 0)
            continue;

        for (unsigned int multiple = factor; multiple < limit; multiple += factor)
        {
            if (!bitmap[multiple])
            {
                result += multiple;
                bitmap[multiple] = true;
            }
        }
    }

    free(bitmap);

    return result;
}
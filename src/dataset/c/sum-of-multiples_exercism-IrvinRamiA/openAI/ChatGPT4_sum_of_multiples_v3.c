#include "sum_of_multiples.h"

unsigned int sum(const unsigned int *factors,
                 const size_t number_of_factors,
                 const unsigned int limit)
{
    unsigned int sum = 0;
    char *is_multiple = (char *)calloc(limit, sizeof(char));

    if (!is_multiple || (number_of_factors == 0 || (number_of_factors == 1 && factors[0] == 0)))
    {
        free(is_multiple);
        return sum;
    }

    for (size_t j = 0; j < number_of_factors; j++)
    {
        unsigned int factor = factors[j];
        if (factor == 0)
            continue;

        for (unsigned int i = factor; i < limit; i += factor)
        {
            if (!is_multiple[i])
            {
                is_multiple[i] = 1;
                sum += i;
            }
        }
    }

    free(is_multiple);
    return sum;
}
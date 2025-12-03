#include "sum_of_multiples.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static inline void set_bit(int *bitmap, size_t index)
{
    bitmap[index >> 5] |= 1 << (index & 31);
}

static inline bool is_set(const int *bitmap, size_t index)
{
    return (bitmap[index >> 5] & (1 << (index & 31))) != 0;
}

unsigned int sum(const unsigned int *factors, const size_t number_of_factors,
                 const unsigned int limit)
{
    if (limit == 0 || number_of_factors == 0)
        return 0;

    size_t bitmap_size = (limit + 31) >> 5;
    int *bitmap = (int *)calloc(bitmap_size, sizeof(int));
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
            if (!is_set(bitmap, multiple))
            {
                result += multiple;
                set_bit(bitmap, multiple);
            }
        }
    }

    free(bitmap);
    return result;
}
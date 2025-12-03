#include "sum_of_multiples.h"

unsigned int sum(const unsigned int *factors,
                 const size_t number_of_factors,
                 const unsigned int limit)
{
    unsigned int sum = 0;
    
    if (number_of_factors == 0 || limit <= 1)
    {
        return sum;
    }

    // Filter out zero factors and duplicates
    unsigned int valid_factors[number_of_factors];
    size_t valid_count = 0;
    
    for (size_t i = 0; i < number_of_factors; i++)
    {
        if (factors[i] != 0 && factors[i] < limit)
        {
            // Check for duplicates
            int is_duplicate = 0;
            for (size_t k = 0; k < valid_count; k++)
            {
                if (valid_factors[k] == factors[i])
                {
                    is_duplicate = 1;
                    break;
                }
            }
            if (!is_duplicate)
            {
                valid_factors[valid_count++] = factors[i];
            }
        }
    }
    
    if (valid_count == 0)
    {
        return sum;
    }

    // Use bit array to mark multiples
    unsigned char *multiples = calloc((limit + 7) / 8, sizeof(unsigned char));
    if (!multiples)
    {
        return sum;
    }

    // Mark all multiples
    for (size_t j = 0; j < valid_count; j++)
    {
        unsigned int factor = valid_factors[j];
        for (unsigned int multiple = factor; multiple < limit; multiple += factor)
        {
            unsigned int byte_index = multiple / 8;
            unsigned int bit_index = multiple % 8;
            multiples[byte_index] |= (1 << bit_index);
        }
    }

    // Sum all marked numbers
    for (unsigned int i = 1; i < limit; i++)
    {
        unsigned int byte_index = i / 8;
        unsigned int bit_index = i % 8;
        if (multiples[byte_index] & (1 << bit_index))
        {
            sum += i;
        }
    }

    free(multiples);
    return sum;
}
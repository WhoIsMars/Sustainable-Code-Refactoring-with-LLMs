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
            bool is_duplicate = false;
            for (size_t k = 0; k < valid_count; k++)
            {
                if (valid_factors[k] == factors[i])
                {
                    is_duplicate = true;
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
    bool is_multiple[limit];
    for (unsigned int i = 0; i < limit; i++)
    {
        is_multiple[i] = false;
    }

    // Mark multiples for each valid factor
    for (size_t j = 0; j < valid_count; j++)
    {
        unsigned int factor = valid_factors[j];
        for (unsigned int multiple = factor; multiple < limit; multiple += factor)
        {
            is_multiple[multiple] = true;
        }
    }

    // Sum all marked multiples
    for (unsigned int i = 1; i < limit; i++)
    {
        if (is_multiple[i])
        {
            sum += i;
        }
    }

    return sum;
}
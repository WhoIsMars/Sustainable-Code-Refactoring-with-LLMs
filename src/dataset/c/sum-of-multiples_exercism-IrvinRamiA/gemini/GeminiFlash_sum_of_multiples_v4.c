#include "sum_of_multiples.h"

unsigned int sum(const unsigned int *factors,
                 const size_t number_of_factors,
                 const unsigned int limit)
{
    unsigned int total_sum = 0;
    bool multiple_found[limit];

    if (number_of_factors == 0) {
        return 0;
    }

    for (unsigned int i = 0; i < limit; ++i) {
        multiple_found[i] = false;
    }

    for (size_t i = 0; i < number_of_factors; ++i) {
        if (factors[i] != 0) {
            for (unsigned int j = factors[i]; j < limit; j += factors[i]) {
                multiple_found[j] = true;
            }
        }
    }

    for (unsigned int i = 1; i < limit; ++i) {
        if (multiple_found[i]) {
            total_sum += i;
        }
    }

    return total_sum;
}
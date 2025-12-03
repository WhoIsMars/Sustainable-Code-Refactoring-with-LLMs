#include "sum_of_multiples.h"
#include <stdlib.h>
#include <stdbool.h>

unsigned int sum(const unsigned int *factors, const size_t number_of_factors,
                 const unsigned int limit) {
    if (!factors || limit == 0) {
        return 0;
    }

    bool *is_multiple = calloc(limit, sizeof(bool));
    if (!is_multiple) {
        return 0;
    }

    unsigned int sum = 0;

    for (size_t i = 0; i < number_of_factors; i++) {
        if (factors[i] == 0) {
            continue;
        }

        for (unsigned int multiple = factors[i]; multiple < limit; multiple += factors[i]) {
            if (!is_multiple[multiple]) {
                is_multiple[multiple] = true;
                sum += multiple;
            }
        }
    }

    free(is_multiple);
    return sum;
}
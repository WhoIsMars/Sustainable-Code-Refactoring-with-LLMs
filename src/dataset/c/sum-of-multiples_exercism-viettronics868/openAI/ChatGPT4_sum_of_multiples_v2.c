#include "sum_of_multiples.h"
#include <stdlib.h>
#include <stdbool.h>

unsigned int sum(const unsigned int *factors, const size_t number_of_factors,
                 const unsigned int limit) {
    unsigned int sum = 0;

    if (factors != NULL && limit > 0) {
        bool *is_multiple = calloc(limit, sizeof(bool));
        if (is_multiple == NULL) {
            return 0; // Memory allocation failed
        }

        for (size_t i = 0; i < number_of_factors; i++) {
            if (factors[i] != 0) {
                for (unsigned int multiple = factors[i]; multiple < limit; multiple += factors[i]) {
                    is_multiple[multiple] = true;
                }
            }
        }

        for (unsigned int i = 0; i < limit; i++) {
            if (is_multiple[i]) {
                sum += i;
            }
        }

        free(is_multiple);
    }

    return sum;
}
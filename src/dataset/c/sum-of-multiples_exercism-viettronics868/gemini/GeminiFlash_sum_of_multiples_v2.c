#include "sum_of_multiples.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

unsigned int sum(const unsigned int *factors, const size_t number_of_factors,
                 const unsigned int limit) {

    unsigned int total_sum = 0;
    if (!factors || limit == 0) {
        return total_sum;
    }

    char *is_multiple = calloc(limit, sizeof(char));
    if (!is_multiple) {
        fprintf(stderr, "Memory allocation failed: %s\n", strerror(errno));
        return 0;
    }

    for (size_t i = 0; i < number_of_factors; ++i) {
        unsigned int factor = factors[i];
        if (factor != 0) {
            for (unsigned int multiple = factor; multiple < limit; multiple += factor) {
                is_multiple[multiple] = 1;
            }
        }
    }

    for (unsigned int i = 0; i < limit; ++i) {
        if (is_multiple[i]) {
            total_sum += i;
        }
    }

    free(is_multiple);
    return total_sum;
}
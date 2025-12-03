#include "sum_of_multiples.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

unsigned int sum(const unsigned int *factors, const size_t number_of_factors,
                 const unsigned int limit) {

    unsigned int sum = 0;
    if (!factors || limit == 0) {
        return sum;
    }

    char *multiples = calloc(limit, sizeof(char));
    if (!multiples) {
        fprintf(stderr, "Memory allocation failed: %s\n", strerror(errno));
        return 0; 
    }

    for (size_t i = 0; i < number_of_factors; i++) {
        if (factors[i] != 0) {
            for (unsigned int j = factors[i]; j < limit; j += factors[i]) {
                multiples[j] = 1;
            }
        }
    }

    for (unsigned int i = 0; i < limit; i++) {
        if (multiples[i]) {
            sum += i;
        }
    }

    free(multiples);
    return sum;
}
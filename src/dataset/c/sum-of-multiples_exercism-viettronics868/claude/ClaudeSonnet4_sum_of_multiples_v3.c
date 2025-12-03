#include "sum_of_multiples.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

unsigned int sum(const unsigned int *factors, const size_t number_of_factors,
                 const unsigned int limit){
    
    if (factors == NULL || limit == 0) {
        return 0;
    }
    
    unsigned char *is_multiple = calloc(limit, sizeof(unsigned char));
    if (is_multiple == NULL) {
        fprintf(stderr, "cannot allocate memory - %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    for (size_t i = 0; i < number_of_factors; i++) {
        if (factors[i] == 0 || factors[i] >= limit) {
            continue;
        }
        
        for (unsigned int multiple = factors[i]; multiple < limit; multiple += factors[i]) {
            is_multiple[multiple] = 1;
        }
    }
    
    unsigned int total_sum = 0;
    for (unsigned int i = 1; i < limit; i++) {
        if (is_multiple[i]) {
            total_sum += i;
        }
    }
    
    free(is_multiple);
    return total_sum;
}
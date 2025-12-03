#include "sum_of_multiples.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

unsigned int sum(const unsigned int *factors, const size_t number_of_factors,
                 const unsigned int limit){
    
    unsigned int sum = 0;

    if ((factors == NULL) || (limit == 0) || (number_of_factors == 0)){
        return 0;
    }
    
    // Use a boolean array to mark multiples
    char *is_multiple = calloc(limit, sizeof(char));
    if (is_multiple == NULL){
        fprintf(stderr, "cannot allocate memory for is_multiple array - %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    // Mark all multiples of each factor
    for (size_t i = 0; i < number_of_factors; i++){
        if (factors[i] != 0 && factors[i] < limit){
            for (unsigned int multiple = factors[i]; multiple < limit; multiple += factors[i]){
                is_multiple[multiple] = 1;
            }
        }
    }
    
    // Sum all marked multiples
    for (unsigned int i = 0; i < limit; i++){
        if (is_multiple[i]){
            sum += i;
        }
    }
    
    free(is_multiple);
    return sum;
}
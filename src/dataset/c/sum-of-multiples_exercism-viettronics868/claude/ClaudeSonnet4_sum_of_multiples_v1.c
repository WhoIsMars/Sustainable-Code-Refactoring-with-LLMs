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
    
    // Use a boolean array to mark multiples (more memory efficient than storing all multiples)
    char *is_multiple = calloc(limit, sizeof(char));
    if (is_multiple == NULL){
        return 0; // Return 0 instead of exiting on allocation failure
    }
    
    // For each factor, mark its multiples directly
    for (size_t i = 0; i < number_of_factors; i++){
        if (factors[i] != 0 && factors[i] < limit){
            // Mark multiples of this factor
            for (unsigned int multiple = factors[i]; multiple < limit; multiple += factors[i]){
                is_multiple[multiple] = 1;
            }
        }
    }
    
    // Sum all marked multiples
    for (unsigned int i = 1; i < limit; i++){
        if (is_multiple[i]){
            sum += i;
        }
    }
    
    free(is_multiple);
    return sum;
}
#include "sum_of_multiples.h"

unsigned int sum(const unsigned int *factors,
                 const size_t number_of_factors,
                 const unsigned int limit)
{
    if (number_of_factors == 0 || limit <= 1) {
        return 0;
    }
    
    unsigned int filtered_factors[number_of_factors];
    size_t filtered_count = 0;
    
    for (size_t i = 0; i < number_of_factors; i++) {
        if (factors[i] != 0 && factors[i] < limit) {
            filtered_factors[filtered_count++] = factors[i];
        }
    }
    
    if (filtered_count == 0) {
        return 0;
    }
    
    unsigned int sum_result = 0;
    unsigned char *is_multiple = calloc(limit, sizeof(unsigned char));
    
    if (!is_multiple) {
        return 0;
    }
    
    for (size_t i = 0; i < filtered_count; i++) {
        unsigned int factor = filtered_factors[i];
        for (unsigned int multiple = factor; multiple < limit; multiple += factor) {
            if (!is_multiple[multiple]) {
                is_multiple[multiple] = 1;
                sum_result += multiple;
            }
        }
    }
    
    free(is_multiple);
    return sum_result;
}
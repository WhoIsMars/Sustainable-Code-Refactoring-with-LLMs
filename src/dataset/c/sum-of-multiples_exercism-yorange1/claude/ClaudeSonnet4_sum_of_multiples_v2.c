#include "sum_of_multiples.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

unsigned int sum(const unsigned int *factors, const size_t number_of_factors,
                 const unsigned int limit)
{
    if (limit <= 1 || number_of_factors == 0) {
        return 0;
    }

    // Use stack allocation for small limits to avoid malloc overhead
    if (limit <= 1024) {
        bool seen[1024] = {false};
        unsigned int result = 0;
        
        for (size_t i = 0; i < number_of_factors; i++) {
            unsigned int factor = factors[i];
            if (factor != 0 && factor < limit) {
                for (unsigned int multiple = factor; multiple < limit; multiple += factor) {
                    if (!seen[multiple]) {
                        seen[multiple] = true;
                        result += multiple;
                    }
                }
            }
        }
        return result;
    }

    // For larger limits, use bitmap with optimized allocation
    size_t bitmap_size = (limit + 31) / 32;
    unsigned int *bitmap = (unsigned int *)calloc(bitmap_size, sizeof(unsigned int));
    if (!bitmap) return 0;

    unsigned int result = 0;

    for (size_t i = 0; i < number_of_factors; i++) {
        unsigned int factor = factors[i];
        if (factor != 0 && factor < limit) {
            for (unsigned int multiple = factor; multiple < limit; multiple += factor) {
                size_t word_index = multiple / 32;
                unsigned int bit_mask = 1U << (multiple % 32);
                
                if (!(bitmap[word_index] & bit_mask)) {
                    bitmap[word_index] |= bit_mask;
                    result += multiple;
                }
            }
        }
    }

    free(bitmap);
    return result;
}
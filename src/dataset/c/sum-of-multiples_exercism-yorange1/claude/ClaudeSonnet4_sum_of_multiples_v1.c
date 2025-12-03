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
    const size_t bitmap_size = (limit + 31) / 32;
    int *bitmap;
    int stack_bitmap[256]; // 8KB stack buffer for limits up to ~8192
    
    if (bitmap_size <= 256) {
        bitmap = stack_bitmap;
        // Clear only needed portion
        for (size_t i = 0; i < bitmap_size; i++) {
            bitmap[i] = 0;
        }
    } else {
        bitmap = (int *)calloc(bitmap_size, sizeof(int));
    }

    unsigned int result = 0;

    for (size_t i = 0; i < number_of_factors; i++) {
        unsigned int factor = factors[i];
        if (factor != 0 && factor < limit) {
            // Direct loop without function calls for better performance
            for (unsigned int multiple = factor; multiple < limit; multiple += factor) {
                size_t word_index = multiple / 32;
                int bit_mask = 1 << (multiple % 32);
                
                if (!(bitmap[word_index] & bit_mask)) {
                    result += multiple;
                    bitmap[word_index] |= bit_mask;
                }
            }
        }
    }

    if (bitmap_size > 256) {
        free(bitmap);
    }

    return result;
}
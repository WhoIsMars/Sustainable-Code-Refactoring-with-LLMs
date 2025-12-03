#include "sum_of_multiples.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

unsigned int sum(const unsigned int *factors, const size_t number_of_factors,
                 const unsigned int limit) {
  if (limit == 0) {
    return 0;
  }

  size_t bitmap_size = (limit + 31) / 32;
  unsigned int *bitmap = (unsigned int *)calloc(bitmap_size, sizeof(unsigned int));
  if (!bitmap) {
    return 0; // Handle allocation failure
  }

  unsigned int result = 0;

  for (size_t i = 0; i < number_of_factors; i++) {
    unsigned int factor = factors[i];
    if (factor != 0) {
      // Start from the factor itself to avoid unnecessary iterations
      for (unsigned int multiple = factor; multiple < limit; multiple += factor) {
        size_t index = multiple -1;
        size_t word_index = index / 32;
        unsigned int bit_mask = 1u << (index % 32);

        if ((bitmap[word_index] & bit_mask) == 0) {
          result += multiple;
          bitmap[word_index] |= bit_mask;
        }
      }
    }
  }

  free(bitmap);
  return result;
}
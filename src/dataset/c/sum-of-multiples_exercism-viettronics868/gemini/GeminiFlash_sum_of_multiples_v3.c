#include "sum_of_multiples.h"
#include <stdbool.h>
#include <stdlib.h>

unsigned int sum(const unsigned int *factors, const size_t number_of_factors,
                 const unsigned int limit) {

  unsigned int sum = 0;

  if (factors == NULL || limit == 0) {
    return sum;
  }

  bool *multiples = calloc(limit, sizeof(bool));
  if (multiples == NULL) {
    return 0;
  }

  for (size_t i = 0; i < number_of_factors; i++) {
    if (factors[i] != 0) {
      for (unsigned int j = factors[i]; j < limit; j += factors[i]) {
        multiples[j] = true;
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
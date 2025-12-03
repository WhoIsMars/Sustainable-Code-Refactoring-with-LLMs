#include "sum_of_multiples.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

unsigned int sum(const unsigned int *factors, const size_t number_of_factors,
                 const unsigned int limit) {

  unsigned int sum = 0;
  if (factors == NULL || limit == 0) {
    return sum;
  }

  char *multiples = calloc(limit, sizeof(char));
  if (multiples == NULL) {
    fprintf(stderr, "Cannot allocate memory: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  for (size_t i = 0; i < number_of_factors; i++) {
    unsigned int factor = factors[i];
    if (factor != 0) {
      for (unsigned int multiple = factor; multiple < limit; multiple += factor) {
        multiples[multiple] = 1;
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
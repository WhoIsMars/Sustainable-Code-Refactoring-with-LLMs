#include "sum_of_multiples.h"

unsigned int sum(const unsigned int *factors,
                 const size_t number_of_factors,
                 const unsigned int limit) {
  unsigned int total_sum = 0;
  bool multiple_found;

  if (factors == NULL || number_of_factors == 0) {
    return 0;
  }

  // Early return if the first factor is zero (and no other factors exist or are non-zero)
  bool all_factors_zero = true;
  for (size_t i = 0; i < number_of_factors; ++i) {
    if (factors[i] != 0) {
      all_factors_zero = false;
      break;
    }
  }
  if (all_factors_zero) {
    return 0;
  }

  for (unsigned int i = 1; i < limit; ++i) {
    multiple_found = false;
    for (size_t j = 0; j < number_of_factors; ++j) {
      if (factors[j] != 0 && i % factors[j] == 0) {
        total_sum += i;
        multiple_found = true;
        break; // Optimization: Once a multiple is found, no need to check other factors
      }
    }
  }

  return total_sum;
}
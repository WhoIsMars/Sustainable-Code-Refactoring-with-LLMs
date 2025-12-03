#include "largest_series_product.h"

#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

int64_t largest_series_product(char *digits, size_t span) {
  assert(digits != NULL);

  size_t len = strlen(digits);

  if (span == 0) {
    return 1;
  }

  if (len == 0 || span > len) {
    return -1;
  }

  int64_t max_product = 0;
  int64_t current_product = 1;

  // Initial product calculation
  for (size_t i = 0; i < span; ++i) {
    if (!isdigit(digits[i])) {
      return -1;
    }
    current_product *= (digits[i] - '0');
  }

  max_product = current_product;

  // Sliding window approach
  for (size_t i = span; i < len; ++i) {
    if (!isdigit(digits[i])) {
      return -1;
    }

    current_product /= (digits[i - span] - '0');
    current_product *= (digits[i] - '0');

    if (current_product > max_product) {
      max_product = current_product;
    }
  }

  return max_product;
}
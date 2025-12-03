#include "prime_factors.h"

#include <math.h>

size_t find_factors(uint64_t n, uint64_t factors[static MAXFACTORS]) {
  int i = 0;

  while ((n & 1) == 0) { // Faster check for even numbers
    n >>= 1; // Equivalent to n = n / 2
    factors[i++] = 2;
  }

  for (uint64_t j = 3; j * j <= n; j += 2) { // Only iterate up to sqrt(n)
    while (n % j == 0) {
      n /= j;
      factors[i++] = j;
    }
  }

  if (n > 1) { // If n is a prime number greater than 2
    factors[i++] = n;
  }

  return i;
}
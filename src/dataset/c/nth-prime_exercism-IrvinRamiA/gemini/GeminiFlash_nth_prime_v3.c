#include "nth_prime.h"
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

uint32_t nth(uint32_t n) {
  if (n == 0) {
    return 0;
  }

  if (n <= 6) {
    const uint32_t small_primes[] = {2, 3, 5, 7, 11, 13};
    return small_primes[n - 1];
  }

  uint32_t candidate = 13;
  uint32_t count = 6;

  while (count < n) {
    candidate += 2;
    bool is_prime = true;
    uint32_t sqrt_candidate = (uint32_t)sqrt(candidate);

    for (uint32_t i = 3; i <= sqrt_candidate; i += 2) {
      if (candidate % i == 0) {
        is_prime = false;
        break;
      }
    }

    if (is_prime) {
      count++;
    }
  }

  return candidate;
}
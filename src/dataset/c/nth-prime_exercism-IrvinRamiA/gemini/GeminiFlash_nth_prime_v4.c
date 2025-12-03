#include "nth_prime.h"
#include <stdbool.h>
#include <math.h>

static bool is_prime(uint32_t number) {
  if (number <= 1) return false;
  if (number <= 3) return true;
  if (number % 2 == 0 || number % 3 == 0) return false;

  for (uint32_t i = 5; i * i <= number; i += 6) {
    if (number % i == 0 || number % (i + 2) == 0) return false;
  }

  return true;
}

uint32_t nth(uint32_t n) {
  if (n == 0) return 0;

  uint32_t candidate = 2;
  uint32_t count = 0;

  while (count < n) {
    if (is_prime(candidate)) {
      count++;
    }
    if (count == n) break;
    candidate++;
  }

  return candidate;
}
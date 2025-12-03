#include "nth_prime.h"

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static bool is_prime(uint32_t n) {
  if (n <= 1) {
    return false;
  }
  if (n <= 3) {
    return true;
  }
  if (n % 2 == 0 || n % 3 == 0) {
    return false;
  }
  for (uint32_t i = 5; i * i <= n; i = i + 6) {
    if (n % i == 0 || n % (i + 2) == 0) {
      return false;
    }
  }
  return true;
}

uint32_t nth(uint32_t n) {
  if (n == 0) {
    return 0;
  }

  uint32_t count = 0;
  uint32_t candidate = 2;

  while (count < n) {
    if (is_prime(candidate)) {
      count++;
    }
    if (count < n) {
      candidate++;
    }
  }

  return candidate;
}
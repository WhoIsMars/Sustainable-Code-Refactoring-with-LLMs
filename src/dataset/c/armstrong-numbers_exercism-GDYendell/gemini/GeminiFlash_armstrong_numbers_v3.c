#include "armstrong_numbers.h"

#include <stdbool.h>
#include <stdint.h>

static uint32_t power(uint32_t base, uint8_t exponent) {
  uint32_t result = 1;
  for (uint8_t i = 0; i < exponent; ++i) {
    if (result > UINT32_MAX / base) return UINT32_MAX;
    result *= base;
  }
  return result;
}

bool is_armstrong_number(int candidate) {
  if (candidate < 0) return false;

  uint32_t num = (uint32_t)candidate;
  uint8_t num_digits = 0;
  uint32_t temp = num;

  if (num == 0) {
    num_digits = 1;
  } else {
    while (temp != 0) {
      temp /= 10;
      num_digits++;
    }
  }

  uint32_t armstrong_sum = 0;
  temp = num;

  while (temp != 0) {
    uint8_t digit = temp % 10;
    uint32_t pow_val = power(digit, num_digits);

    if (UINT32_MAX - armstrong_sum < pow_val) return false;

    armstrong_sum += pow_val;
    temp /= 10;
  }

  return (uint32_t)candidate == armstrong_sum;
}
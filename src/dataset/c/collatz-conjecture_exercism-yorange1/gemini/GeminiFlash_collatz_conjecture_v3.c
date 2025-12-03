#include "collatz_conjecture.h"

#define is_even(n) ((n & 1) == 0)

int steps(int start) {
  if (start <= 0) {
    return ERROR_VALUE;
  }

  int count = 0;
  unsigned int n = (unsigned int)start;

  while (n != 1) {
    if (is_even(n)) {
      n >>= 1;
    } else {
      if (n > (UINT_MAX - 1) / 3) {
        return ERROR_VALUE;
      }
      n = n * 3 + 1;
      if (n < start) {
          return ERROR_VALUE;
      }
    }
    count++;
  }

  return count;
}
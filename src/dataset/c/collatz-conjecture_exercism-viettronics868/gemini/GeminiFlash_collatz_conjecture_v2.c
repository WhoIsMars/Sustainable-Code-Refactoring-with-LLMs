#include "collatz_conjecture.h"

int steps(int start) {
  if (start <= 0) {
    return -1;
  }

  int count = 0;
  unsigned int n = (unsigned int)start; // Use unsigned int to avoid potential overflow

  while (n != 1) {
    if ((n & 1) == 0) { // Use bitwise AND for even number check (faster)
      n >>= 1;         // Use right bit shift for division by 2 (faster)
    } else {
      if (n > (UINT_MAX - 1) / 3) return -1; // Check for potential overflow before multiplication
      n = (n * 3) + 1;
    }
    count++;
  }
  return count;
}
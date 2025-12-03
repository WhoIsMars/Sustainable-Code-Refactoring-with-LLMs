#include "collatz_conjecture.h"

int steps(int start) {
  if (start <= 0) {
    return ERROR_VALUE;
  }

  int step_count = 0;

  while (start != 1) {
    if ((start & 1) == 0) { // Use bitwise AND for even number check
      start >>= 1;          // Use right bit shift for division by 2
    } else {
      if (start > (INT_MAX - 1) / 3) return ERROR_VALUE; // Check for potential overflow before multiplication
      start = 3 * start + 1;
      if (start < 0) return ERROR_VALUE; // Check for overflow after multiplication
    }
    step_count++;
  }

  return step_count;
}
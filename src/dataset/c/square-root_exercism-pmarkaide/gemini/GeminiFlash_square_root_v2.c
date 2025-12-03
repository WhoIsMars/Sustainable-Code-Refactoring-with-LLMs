#include "square_root.h"

unsigned int square_root(unsigned int number) {
  if (number == 0) return 0;

  unsigned int low = 1, high = number;
  unsigned int result = -1;

  while (low <= high) {
    unsigned int mid = low + (high - low) / 2;  // Prevent potential overflow
    unsigned int square = number / mid;

    if (square == mid) {
      if (number % mid == 0) return mid;
      else high = mid -1;
    } else if (square > mid) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return result;
}
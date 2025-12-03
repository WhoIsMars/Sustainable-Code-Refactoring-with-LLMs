#include "square_root.h"

unsigned int square_root(unsigned int number) {
  if (number == 0) return 0;
  if (number == 1) return 1;

  unsigned int low = 1;
  unsigned int high = number / 2;
  unsigned int result = -1;

  while (low <= high) {
    unsigned int mid = low + (high - low) / 2;
    unsigned int square = number / mid; // Avoid potential overflow

    if (square == mid) {
      if (number % mid == 0) // Check for perfect square
        return mid;
      else
        high = mid -1;
    } else if (square > mid) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }

  return result;
}
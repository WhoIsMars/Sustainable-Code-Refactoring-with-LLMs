#include "collatz_conjecture.h"
#include <stdexcept>

int collatz_conjecture::steps(int number) {
  if (number <= 0) {
    throw std::domain_error("Non-positive side is illegal.");
  }

  int step = 0;
  while (number > 1) {
    if ((number & 1) == 0) {
      number >>= 1;
    } else {
      if (number > (INT_MAX - 1) / 3) {
          throw std::overflow_error("Potential overflow");
      }
      number = 3 * number + 1;
    }
    step++;
  }
  return step;
}
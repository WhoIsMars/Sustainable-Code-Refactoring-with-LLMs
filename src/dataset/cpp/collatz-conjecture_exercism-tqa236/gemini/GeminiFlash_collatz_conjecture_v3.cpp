#include "collatz_conjecture.h"
#include <stdexcept>

int collatz_conjecture::steps(int number) {
  if (number <= 0) throw std::domain_error("Non-positive side is illegal.");
  int step = 0;
  unsigned int n = static_cast<unsigned int>(number);
  while (n > 1) {
    if ((n & 1) == 0) {
      n >>= 1;
    } else {
      if (n > (UINT_MAX - 1) / 3) {
          throw std::overflow_error("Collatz sequence exceeds maximum representable value.");
      }
      n = 3 * n + 1;
    }
    step += 1;
  }
  return step;
}
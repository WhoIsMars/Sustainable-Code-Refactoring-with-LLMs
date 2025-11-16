#include "collatz_conjecture.h"
#include <stdexcept>

int collatz_conjecture::steps(int number) {
  if (number <= 0) throw std::domain_error("Non-positive side is illegal.");
  int step = 0;
  while (number != 1) {
    step += 1 + __builtin_ctz(number);
    number >>= __builtin_ctz(number);
    if (number == 1) break;
    number = 3 * number + 1;
  }
  return step;
}
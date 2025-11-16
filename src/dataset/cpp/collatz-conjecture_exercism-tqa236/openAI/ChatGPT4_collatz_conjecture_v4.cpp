#include "collatz_conjecture.h"
#include <stdexcept>

int collatz_conjecture::steps(int number) {
  if (number <= 0) throw std::domain_error("Non-positive side is illegal.");
  int step = 0;
  while (number > 1) {
    number = (number % 2 == 0) ? (number / 2) : (3 * number + 1);
    ++step;
  }
  return step;
}
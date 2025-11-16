#include "perfect_numbers.h"

#include <stdexcept>
#include <cmath>

namespace perfect_numbers {

classification classify(int number) {
  if (number <= 0) {
    throw std::domain_error("Number invalid.");
  }

  if (number == 1) return classification::deficient;

  int sum_of_factors = 1; // 1 is always a divisor

  // Iterate only up to the square root of the number.
  for (int i = 2; i <= std::sqrt(number); ++i) {
    if (number % i == 0) {
      sum_of_factors += i;
      int other_factor = number / i;
      if (other_factor != i) {
        sum_of_factors += other_factor;
      }
    }
  }

  if (sum_of_factors == number) {
    return classification::perfect;
  } else if (sum_of_factors < number) {
    return classification::deficient;
  } else {
    return classification::abundant;
  }
}

} // namespace perfect_numbers
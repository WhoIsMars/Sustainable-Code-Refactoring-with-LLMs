#include "triangle.h"

#include <stdexcept>

namespace triangle {
static void check_valid_triangle(double const side1, double const side2,
                                 double const side3) {
  if (side1 <= 0 || side2 <= 0 || side3 <= 0) {
    throw std::domain_error("Non-positive side is illegal.");
  }
  
  double max_side, sum_other_two;
  if (side1 >= side2 && side1 >= side3) {
    max_side = side1;
    sum_other_two = side2 + side3;
  } else if (side2 >= side3) {
    max_side = side2;
    sum_other_two = side1 + side3;
  } else {
    max_side = side3;
    sum_other_two = side1 + side2;
  }
  
  if (max_side >= sum_other_two) {
    throw std::domain_error("Violate triangle inequality.");
  }
}

flavor kind(double const side1, double const side2, double const side3) {
  check_valid_triangle(side1, side2, side3);

  const bool eq12 = (side1 == side2);
  const bool eq13 = (side1 == side3);
  const bool eq23 = (side2 == side3);
  
  if (eq12 && eq13) return equilateral;
  if (eq12 || eq13 || eq23) return isosceles;
  return scalene;
}
}  // namespace triangle
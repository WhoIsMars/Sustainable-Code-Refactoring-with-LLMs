#include "triangle.h"

#include <stdexcept>

namespace triangle {
static void check_valid_triangle(double const side1, double const side2,
                                 double const side3) {
  if (side1 <= 0 || side2 <= 0 || side3 <= 0) {
    throw std::domain_error("Non-positive side is illegal.");
  }
  
  const double sum = side1 + side2 + side3;
  if (side1 >= sum - side1 || side2 >= sum - side2 || side3 >= sum - side3) {
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
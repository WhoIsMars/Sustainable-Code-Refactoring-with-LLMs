#include "triangle.h"

#include <stdexcept>

namespace triangle {
static void check_valid_triangle(double side1, double side2, double side3) {
  if (side1 <= 0 || side2 <= 0 || side3 <= 0) {
    throw std::domain_error("Non-positive side is illegal.");
  }
  if (side1 + side2 <= side3 || side1 + side3 <= side2 || side2 + side3 <= side1) {
    throw std::domain_error("Violate triangle inequality.");
  }
}

flavor kind(double side1, double side2, double side3) {
  check_valid_triangle(side1, side2, side3);

  if (side1 == side2 && side2 == side3) return equilateral;
  if (side1 == side2 || side1 == side3 || side2 == side3) return isosceles;
  return scalene;
}
}  // namespace triangle
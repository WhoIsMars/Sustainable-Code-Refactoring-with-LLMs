#include "triangle.h"

#include <algorithm>
#include <stdexcept>

namespace triangle {
static void check_valid_triangle(double const side1, double const side2,
                                 double const side3) {
  if (std::min({side1, side2, side3}) <= 0) {
    throw std::domain_error("Non-positive side is illegal.");
  }
  if (std::max({side1, side2, side3}) >= (side1 + side2 + side3) / 2) {
    throw std::domain_error("Violate triangle inequality.");
  }
}

flavor kind(double const side1, double const side2, double const side3) {
  check_valid_triangle(side1, side2, side3);

  const int point = (side1 == side2) + (side1 == side3) + (side2 == side3);
  if (point == 3) return equilateral;
  if (point == 1) return isosceles;
  return scalene;
}
}  // namespace triangle

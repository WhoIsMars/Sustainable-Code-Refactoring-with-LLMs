#include "triangle.h"
#include <algorithm>

namespace triangle {
  flavor kind(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0) {
      throw std::domain_error("All triangle sides must have a length greater than zero.");
    }

    double sides[] = {a, b, c};
    std::sort(sides, sides + 3);

    if (sides[0] + sides[1] < sides[2]) {
      throw std::domain_error("Combined length of any two triangle sides must be greater or equal to length of third side.");
    }

    if (sides[0] == sides[2]) {
      return flavor::equilateral;
    } else if (sides[0] == sides[1] || sides[1] == sides[2]) {
      return flavor::isosceles;
    }

    return flavor::scalene;
  }
}  // namespace triangle
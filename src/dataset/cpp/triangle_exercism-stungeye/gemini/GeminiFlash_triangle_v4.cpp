#include "triangle.h"
#include <algorithm>
#include <cmath>

namespace triangle {
  flavor kind(double a, double b, double c) {
    if (!(a > 0 && b > 0 && c > 0)) {
      throw std::domain_error("All triangle sides must have a length greater than zero.");
    }

    double sides[3] = {a, b, c};
    std::sort(sides, sides + 3);

    if (!(sides[0] + sides[1] > sides[2])) {
      throw std::domain_error("Combined length of any two triangle sides much be greater or equal to length of third side.");
    }

    if (a == b) {
        if (b == c) {
            return flavor::equilateral;
        } else {
            return flavor::isosceles;
        }
    } else if (b == c || a == c) {
        return flavor::isosceles;
    }

    return flavor::scalene;
  }
}  // namespace triangle
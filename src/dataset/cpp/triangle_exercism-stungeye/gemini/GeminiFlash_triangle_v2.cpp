#include "triangle.h"
#include <algorithm>

namespace triangle {
  flavor kind(double a, double b, double c) {
    if ((a <= 0) || (b <= 0) || (c <= 0)) {
      throw std::domain_error("All triangle sides must have a length greater than zero.");
     }

    if ((a + b <= c) || (a + c <= b) || (b + c <= a)) { 
      throw std::domain_error("Combined length of any two triangle sides much be greater or equal to length of third side.");
    }

    if (a == b) {
        if (b == c) {
            return flavor::equilateral;
        } else {
            return flavor::isosceles;
        }
    } else if ((a == c) || (b == c)) {
        return flavor::isosceles;
    }

    return flavor::scalene;
  }
}  // namespace triangle
#include "triangle.h"

namespace triangle {
  flavor kind(double a, double b, double c) {
    if ((a <= 0) || (b <= 0) || (c <= 0)) {
      throw std::domain_error("All triangle sides must have a length greater than zero.");
    }

    // Sort sides to minimize comparisons
    if (a > b) std::swap(a, b);
    if (b > c) std::swap(b, c);
    if (a > b) std::swap(a, b);

    // Triangle inequality check (only need to check smallest + middle > largest)
    if (a + b <= c) {
      throw std::domain_error("Combined length of any two triangle sides much be greater or equal to length of third side.");
    }

    // Check triangle type with early returns
    if (a == c) {
      return flavor::equilateral;
    }
    
    if ((a == b) || (b == c)) {
      return flavor::isosceles;
    }

    return flavor::scalene;
  }
}  // namespace triangle
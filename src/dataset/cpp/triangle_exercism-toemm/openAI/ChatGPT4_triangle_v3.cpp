#include "triangle.h"

#include <stdexcept>
#include <cmath>

namespace triangle {

    flavor kind(float a, float b, float c) {
        if (a <= 0 || b <= 0 || c <= 0 || a + b < c || b + c < a || a + c < b) {
            throw std::domain_error("invalid triangle");
        }

        if (std::fabs(a - b) < 1e-6 && std::fabs(a - c) < 1e-6) {
            return flavor::equilateral;
        }
        if (std::fabs(a - b) < 1e-6 || std::fabs(a - c) < 1e-6 || std::fabs(b - c) < 1e-6) {
            return flavor::isosceles;
        }
        return flavor::scalene;
    }
}  // namespace triangle
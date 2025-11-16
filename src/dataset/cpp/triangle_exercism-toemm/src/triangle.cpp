#include "triangle.h"

#include <stdexcept>

namespace triangle {



    flavor kind(float a, float b, float c) {

        if (!((a + b >= c and b + c >= a and a + c >= b) and (a > 0 and b > 0 and c > 0)))
        {
            throw std::domain_error("invalid triangle");
        }

        if (a == b and a == c) return flavor::equilateral;
        if (a == b or a == c or b == c) return flavor::isosceles;
        if (a != b && a != c) return flavor::scalene;

        return flavor::equilateral;

    }
}  // namespace triangle

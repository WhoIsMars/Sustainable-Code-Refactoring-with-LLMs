#include "triangle.h"

#include <stdexcept>

namespace triangle {

    flavor kind(float a, float b, float c) {
        // Early validation - check positive values first (cheaper than triangle inequality)
        if (a <= 0 || b <= 0 || c <= 0) {
            throw std::domain_error("invalid triangle");
        }
        
        // Triangle inequality check
        if (a + b <= c || b + c <= a || a + c <= b) {
            throw std::domain_error("invalid triangle");
        }

        // Check equilateral first (most restrictive)
        if (a == b && a == c) return flavor::equilateral;
        
        // Check isosceles (any two sides equal)
        if (a == b || a == c || b == c) return flavor::isosceles;
        
        // If not equilateral or isosceles, must be scalene
        return flavor::scalene;
    }

}  // namespace triangle
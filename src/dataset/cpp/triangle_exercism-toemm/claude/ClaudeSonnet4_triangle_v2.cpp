#include "triangle.h"

#include <stdexcept>

namespace triangle {

    flavor kind(float a, float b, float c) {
        // Early validation - check positivity first (cheaper than addition)
        if (a <= 0 || b <= 0 || c <= 0) {
            throw std::domain_error("invalid triangle");
        }
        
        // Triangle inequality check
        if (a + b <= c || b + c <= a || a + c <= b) {
            throw std::domain_error("invalid triangle");
        }

        // Check equality conditions in order of likelihood
        if (a == b) {
            return (a == c) ? flavor::equilateral : flavor::isosceles;
        }
        if (a == c || b == c) {
            return flavor::isosceles;
        }
        
        return flavor::scalene;
    }

}  // namespace triangle
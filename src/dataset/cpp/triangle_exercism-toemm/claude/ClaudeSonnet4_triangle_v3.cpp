#include "triangle.h"

#include <stdexcept>

namespace triangle {

    flavor kind(float a, float b, float c) {
        if (a <= 0 || b <= 0 || c <= 0 || 
            a + b <= c || b + c <= a || a + c <= b) {
            throw std::domain_error("invalid triangle");
        }

        if (a == b) {
            return (a == c) ? flavor::equilateral : flavor::isosceles;
        }
        
        if (a == c || b == c) {
            return flavor::isosceles;
        }
        
        return flavor::scalene;
    }

}  // namespace triangle
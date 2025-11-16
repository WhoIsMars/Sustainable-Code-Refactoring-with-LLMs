#include "triangle.h"
#include <stdexcept>

namespace triangle {
    flavor kind(double s1, double s2, double s3) {
        // Inline validation to avoid function call overhead
        if (s1 <= 0 || s2 <= 0 || s3 <= 0 || 
            (s1 + s2) <= s3 || (s2 + s3) <= s1 || (s1 + s3) <= s2) {
            throw std::domain_error("not a legal triangle");
        }
        
        // Use bitwise operations to track equality
        const bool s1_eq_s2 = (s1 == s2);
        const bool s2_eq_s3 = (s2 == s3);
        const bool s1_eq_s3 = (s1 == s3);
        
        if (s1_eq_s2 && s2_eq_s3) {
            return flavor::equilateral;
        }
        if (s1_eq_s2 || s2_eq_s3 || s1_eq_s3) {
            return flavor::isosceles;
        }
        
        return flavor::scalene;
    }

    bool is_legal_triangle(double s1, double s2, double s3) {
        return s1 > 0 && s2 > 0 && s3 > 0 && 
               (s1 + s2) > s3 && (s2 + s3) > s1 && (s1 + s3) > s2;
    }
}  // namespace triangle
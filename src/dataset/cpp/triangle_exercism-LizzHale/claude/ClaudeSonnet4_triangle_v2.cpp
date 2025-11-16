#include "triangle.h"
#include <stdexcept>

namespace triangle {
    flavor kind(double s1, double s2, double s3) {
        // Combined validation and classification in single pass
        if (s1 <= 0 || s2 <= 0 || s3 <= 0) {
            throw std::domain_error("not a legal triangle");
        }
        
        if ((s1 + s2) <= s3 || (s2 + s3) <= s1 || (s1 + s3) <= s2) {
            throw std::domain_error("not a legal triangle");
        }
        
        // Count equal sides using bitwise operations for efficiency
        int equal_count = (s1 == s2) + (s2 == s3) + (s1 == s3);
        
        if (equal_count == 3) {
            return flavor::equilateral;
        } else if (equal_count > 0) {
            return flavor::isosceles;
        }
        
        return flavor::scalene;
    }

    bool is_legal_triangle(double s1, double s2, double s3) {
        return (s1 > 0 && s2 > 0 && s3 > 0) &&
               ((s1 + s2) > s3 && (s2 + s3) > s1 && (s1 + s3) > s2);
    }
}  // namespace triangle
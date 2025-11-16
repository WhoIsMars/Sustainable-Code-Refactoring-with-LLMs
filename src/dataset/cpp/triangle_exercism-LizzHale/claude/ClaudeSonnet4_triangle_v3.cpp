#include "triangle.h"
#include <stdexcept>

namespace triangle {
    flavor kind(double s1, double s2, double s3) {
        if (s1 <= 0 || s2 <= 0 || s3 <= 0 ||
            (s1 + s2) <= s3 || (s2 + s3) <= s1 || (s1 + s3) <= s2) {
            throw std::domain_error("not a legal triangle");
        }
        
        if (s1 == s2) {
            return (s2 == s3) ? flavor::equilateral : flavor::isosceles;
        }
        
        return (s2 == s3 || s1 == s3) ? flavor::isosceles : flavor::scalene;
    }

    bool is_legal_triangle(double s1, double s2, double s3) {
        return s1 > 0 && s2 > 0 && s3 > 0 &&
               (s1 + s2) > s3 && (s2 + s3) > s1 && (s1 + s3) > s2;
    }
}
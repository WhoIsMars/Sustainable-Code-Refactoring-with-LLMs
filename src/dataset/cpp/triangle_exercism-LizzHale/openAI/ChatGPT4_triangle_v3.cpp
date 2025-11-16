#include "triangle.h"
#include <stdexcept>
#include <algorithm>

namespace triangle {
    flavor kind(double s1, double s2, double s3) {
        if (s1 <= 0 || s2 <= 0 || s3 <= 0 || 
            s1 + s2 <= s3 || s2 + s3 <= s1 || s1 + s3 <= s2) {
            throw std::domain_error("not a legal triangle");
        }

        if (s1 == s2 && s2 == s3) {
            return flavor::equilateral;
        }
        if (s1 == s2 || s2 == s3 || s1 == s3) {
            return flavor::isosceles;
        }

        return flavor::scalene;
    }
}  // namespace triangle
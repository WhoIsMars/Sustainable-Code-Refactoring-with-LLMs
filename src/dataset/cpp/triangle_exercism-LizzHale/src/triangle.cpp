#include "triangle.h"
#include <stdexcept>

namespace triangle {
    flavor kind(double s1, double s2, double s3) {
        if (!is_legal_triangle(s1, s2, s3)) {
            throw std::domain_error("not a legal triangle");
        }
        if (s1 == s2 && s2 == s3) {
            return flavor::equilateral;
        }
        else if (s1 == s2 || s2 == s3 || s1 == s3) {
            return flavor::isosceles;
        }

        return flavor::scalene;
    }

    bool is_legal_triangle(double s1, double s2, double s3) {
        if (s1 <= 0 || s2 <= 0 || s3 <=0) {
            return false;
        }
        if ((s1 + s2) < s3 || (s2 + s3) < s1 || (s1 + s3) < s2) {
            return false;
        }
        return true;
    }
}  // namespace triangle

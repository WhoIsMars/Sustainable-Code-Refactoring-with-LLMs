#include "triangle.h"
#include <stdexcept>
#include <algorithm>

namespace triangle {
    flavor kind(double s1, double s2, double s3) {
        double sides[] = {s1, s2, s3};
        std::sort(sides, sides + 3);

        if (sides[0] <= 0 || sides[0] + sides[1] <= sides[2]) {
            throw std::domain_error("not a legal triangle");
        }

        if (sides[0] == sides[2]) {
            return flavor::equilateral;
        }
        if (sides[0] == sides[1] || sides[1] == sides[2]) {
            return flavor::isosceles;
        }

        return flavor::scalene;
    }
}  // namespace triangle
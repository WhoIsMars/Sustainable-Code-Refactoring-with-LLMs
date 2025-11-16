#include "triangle.h"
#include <stdexcept>
#include <algorithm>

namespace triangle {
    flavor kind(double x, double y, double z) {
        if (x <= 0 || y <= 0 || z <= 0)
            throw std::domain_error("Wrong input data - invalid triangle");

        double sides[] = {x, y, z};
        std::sort(sides, sides + 3);

        if (sides[0] + sides[1] <= sides[2])
            throw std::domain_error("Wrong input data - invalid triangle");

        if (sides[0] == sides[2])
            return flavor::equilateral;
        if (sides[0] == sides[1] || sides[1] == sides[2])
            return flavor::isosceles;
        return flavor::scalene;
    }
}
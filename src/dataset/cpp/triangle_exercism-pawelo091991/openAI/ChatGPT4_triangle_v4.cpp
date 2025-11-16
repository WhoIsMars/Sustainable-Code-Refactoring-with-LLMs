#include "triangle.h"
#include <stdexcept>

namespace triangle {
    flavor kind(double x, double y, double z) {
        if (x <= 0 || y <= 0 || z <= 0 || x + y <= z || x + z <= y || z + y <= x)
            throw std::domain_error("Wrong input data - invalid triangle");

        if (x == y && y == z)
            return flavor::equilateral;

        if (x == y || x == z || y == z)
            return flavor::isosceles;

        return flavor::scalene;
    }
}
#include <stdexcept>
#include <algorithm>
#include "triangle.h"

namespace triangle {
    flavor kind(double side1, double side2, double side3) {
        validate(side1, side2, side3);

        if (side1 == side2) {
            if (side2 == side3) {
                return flavor::equilateral;
            } else {
                return flavor::isosceles;
            }
        } else if (side1 == side3 || side2 == side3) {
            return flavor::isosceles;
        } else if (side1 + side2 == side3 || side1 + side3 == side2 || side2 + side3 == side1) {
            return flavor::degenerate;
        } else {
            return flavor::scalene;
        }
    }

    void validate(double side1, double side2, double side3) {
        if (side1 <= 0 || side2 <= 0 || side3 <= 0) {
            throw std::domain_error("All sides must be > 0");
        }

        double sides[3] = {side1, side2, side3};
        std::sort(sides, sides + 3);

        if (sides[0] + sides[1] <= sides[2]) {
            throw std::domain_error("Sum of any two sides must be > to the third side");
        }
    }
}  // namespace triangle
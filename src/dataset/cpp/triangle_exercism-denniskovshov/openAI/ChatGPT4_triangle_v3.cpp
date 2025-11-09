#include <stdexcept>
#include "triangle.h"

namespace triangle {
    flavor kind(double side1, double side2, double side3) {
        validate(side1, side2, side3);

        if (side1 == side2 && side2 == side3) {
            return flavor::equilateral;
        }

        if (side1 + side2 == side3 || side1 + side3 == side2 || side2 + side3 == side1) {
            return flavor::degenerate;
        }

        if (side1 == side2 || side1 == side3 || side2 == side3) {
            return flavor::isosceles;
        }

        return flavor::scalene;
    }

    void validate(double side1, double side2, double side3) {
        if (side1 <= 0 || side2 <= 0 || side3 <= 0 || 
            side1 + side2 < side3 || side1 + side3 < side2 || side2 + side3 < side1) {
            throw std::domain_error("Invalid triangle sides");
        }
    }
}  // namespace triangle
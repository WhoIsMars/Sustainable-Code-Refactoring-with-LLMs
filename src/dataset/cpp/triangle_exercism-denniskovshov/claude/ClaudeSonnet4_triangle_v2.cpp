#include <stdexcept>
#include "triangle.h"

namespace triangle {
    flavor kind(double side1, double side2, double side3) {
        validate(side1, side2, side3);

        // Check for equilateral first (most restrictive)
        if (side1 == side2 && side2 == side3)
            return flavor::equilateral;

        // Check for degenerate (already computed sums in validate)
        if (side1 + side2 == side3 || side1 + side3 == side2 || side2 + side3 == side1)
            return flavor::degenerate;

        // Check for isosceles (at least two sides equal)
        if (side1 == side2 || side1 == side3 || side2 == side3)
            return flavor::isosceles;

        // If none of the above, it's scalene
        return flavor::scalene;
    }

    void validate(double side1, double side2, double side3) {
        if (side1 <= 0 || side2 <= 0 || side3 <= 0)
            throw std::domain_error("All sides must be > 0");

        if (side1 + side2 < side3 || side1 + side3 < side2 || side2 + side3 < side1)
            throw std::domain_error("Sum of any two sides must be >= to the third side");
    }
}  // namespace triangle
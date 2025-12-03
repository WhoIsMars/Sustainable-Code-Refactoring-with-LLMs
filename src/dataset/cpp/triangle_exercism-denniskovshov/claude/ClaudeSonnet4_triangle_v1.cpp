#include <stdexcept>
#include "triangle.h"

namespace triangle {
    flavor kind(double side1, double side2, double side3) {
        validate(side1, side2, side3);

        // Check for degenerate triangle first (most restrictive condition)
        if (side1 + side2 == side3 || side1 + side3 == side2 || side2 + side3 == side1)
            return flavor::degenerate;

        // Count equal sides efficiently
        const bool s1_eq_s2 = (side1 == side2);
        const bool s1_eq_s3 = (side1 == side3);
        const bool s2_eq_s3 = (side2 == side3);

        // An equilateral triangle has all three sides the same length
        if (s1_eq_s2 && s2_eq_s3)
            return flavor::equilateral;

        // An isosceles triangle has at least two sides the same length
        if (s1_eq_s2 || s1_eq_s3 || s2_eq_s3)
            return flavor::isosceles;

        // A scalene triangle has all sides of different lengths
        return flavor::scalene;
    }

    void validate(double side1, double side2, double side3) {
        if (side1 <= 0 || side2 <= 0 || side3 <= 0)
            throw std::domain_error("All sides must be > 0");

        if (side1 + side2 < side3 || side1 + side3 < side2 || side2 + side3 < side1)
            throw std::domain_error("Sum of any two sides must be >= to the third side");
    }
}  // namespace triangle
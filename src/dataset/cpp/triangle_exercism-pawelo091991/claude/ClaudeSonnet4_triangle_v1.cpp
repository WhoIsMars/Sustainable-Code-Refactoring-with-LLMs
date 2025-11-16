#include "triangle.h"
#include <stdexcept>

namespace triangle {
	flavor kind(double x, double y, double z) {
		// Early validation with single condition check
		if (x <= 0 || y <= 0 || z <= 0) {
			throw std::domain_error("Wrong input data - invalid triangle");
		}
		
		// Triangle inequality check with optimized order
		if (x + y <= z || x + z <= y || y + z <= x) {
			throw std::domain_error("Wrong input data - invalid triangle");
		}
		
		// Count equal sides efficiently
		const bool xy_equal = (x == y);
		const bool xz_equal = (x == z);
		const bool yz_equal = (y == z);
		
		const int equal_count = xy_equal + xz_equal + yz_equal;
		
		if (equal_count == 3) return flavor::equilateral;
		if (equal_count > 0) return flavor::isosceles;
		return flavor::scalene;
	}
}
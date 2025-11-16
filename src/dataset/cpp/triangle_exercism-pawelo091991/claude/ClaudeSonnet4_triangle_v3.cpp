#include "triangle.h"
#include <stdexcept>

namespace triangle {
	flavor kind(double x, double y, double z) {
		if (x <= 0 || y <= 0 || z <= 0) {
			throw std::domain_error("Wrong input data - invalid triangle");
		}
		
		if (x + y <= z || x + z <= y || y + z <= x) {
			throw std::domain_error("Wrong input data - invalid triangle");
		}
		
		const bool xy_equal = (x == y);
		const bool xz_equal = (x == z);
		const bool yz_equal = (y == z);
		
		if (xy_equal && xz_equal) {
			return flavor::equilateral;
		}
		
		if (xy_equal || xz_equal || yz_equal) {
			return flavor::isosceles;
		}
		
		return flavor::scalene;
	}
}
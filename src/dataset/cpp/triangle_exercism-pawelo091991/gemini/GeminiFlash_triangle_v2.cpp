#include "triangle.h"
#include <stdexcept>
#include <algorithm>

namespace triangle {
	flavor kind(double x, double y, double z) {
		if (x <= 0 || y <= 0 || z <= 0)
			throw std::domain_error("Wrong input data - invalid triangle");

		if (x + y <= z || x + z <= y || y + z <= x)
			throw std::domain_error("Wrong input data - invalid triangle");

		if (x == y) {
			if (x == z) {
				return flavor::equilateral;
			}
			return flavor::isosceles;
		}
		if (x == z || y == z) {
			return flavor::isosceles;
		}

		return flavor::scalene;
	}
}
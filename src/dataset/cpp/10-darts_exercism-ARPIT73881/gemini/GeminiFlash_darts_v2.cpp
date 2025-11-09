#include "darts.h"
#include <cmath>

namespace darts {
	int score(double x, double y) {
		// Calculate squared distance from the center
		double distance_squared = x * x + y * y;

		// Scoring based on distance, using squared values for efficiency
		if (distance_squared > 100.0) {
			return 0;
		}
		if (distance_squared > 25.0) {
			return 1;
		}
		if (distance_squared > 1.0) {
			return 5;
		}
		return 10;
	}
} // namespace darts
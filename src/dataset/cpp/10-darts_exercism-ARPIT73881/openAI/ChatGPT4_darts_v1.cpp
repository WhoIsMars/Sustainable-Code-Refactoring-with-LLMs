#include "darts.h"

namespace darts {
	int score(double x, double y) {
		// Calculate squared distance to avoid costly sqrt operation
		double distanceSquared = x * x + y * y;

		// Scoring based on squared distance
		if (distanceSquared > 100.0) {
			return 0; // Outside of the outer circle
		} else if (distanceSquared > 25.0) {
			return 1; // Within the outer circle
		} else if (distanceSquared > 1.0) {
			return 5; // Within the middle circle
		} else {
			return 10; // Within the inner circle (including the center)
		}
	}
} // namespace darts
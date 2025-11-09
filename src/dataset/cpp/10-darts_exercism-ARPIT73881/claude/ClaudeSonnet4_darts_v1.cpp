#include "darts.h"

namespace darts {
	int score(double x, double y) {
		// Use squared distance to avoid expensive sqrt operation
		double distance_squared = x * x + y * y;

		// Compare with squared thresholds (10^2=100, 5^2=25, 1^2=1)
		if (distance_squared > 100.0) {
			return 0;
		}
		else if (distance_squared > 25.0) {
			return 1;
		}
		else if (distance_squared > 1.0) {
			return 5;
		}
		else {
			return 10;
		}
	}
} // namespace darts
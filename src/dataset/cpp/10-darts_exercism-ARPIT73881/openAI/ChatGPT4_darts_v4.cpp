#include "darts.h"

namespace darts {
	int score(double x, double y) {
		double distanceSquared = x * x + y * y;

		if (distanceSquared > 100.0) return 0;
		if (distanceSquared > 25.0) return 1;
		if (distanceSquared > 1.0) return 5;
		return 10;
	}
} // namespace darts
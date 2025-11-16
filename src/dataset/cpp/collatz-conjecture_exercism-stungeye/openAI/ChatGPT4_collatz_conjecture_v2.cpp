#include "collatz_conjecture.h"

#include <stdexcept>

namespace collatz_conjecture {
	// Optimized Iterative Solution
	int steps(int n) {
		if (n <= 0) throw std::domain_error("Argument must be greater than zero.");

		int stepCount = 0;

		while (n != 1) {
			// Use bitwise operations for efficiency
			n = (n & 1) ? (3 * n + 1) : (n >> 1);
			++stepCount;
		}

		return stepCount;
	}
}  // namespace collatz_conjecture
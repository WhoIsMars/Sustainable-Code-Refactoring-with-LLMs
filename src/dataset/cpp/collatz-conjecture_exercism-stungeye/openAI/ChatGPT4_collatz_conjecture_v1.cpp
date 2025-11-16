#include "collatz_conjecture.h"

#include <stdexcept>

namespace collatz_conjecture {
	// Optimized Iterative Solution
	int steps(int n) {
		if (n <= 0) throw std::domain_error("Argument must be greater than zero.");

		int stepCount = 0;

		while (n != 1) {
			if (n & 1) { // Check if n is odd
				// Use unsigned long long to prevent overflow for large n
				if (n > (std::numeric_limits<int>::max() - 1) / 3) {
					throw std::overflow_error("Integer overflow during computation.");
				}
				n = 3 * n + 1;
			} else {
				n >>= 1; // Use bitwise shift for division by 2
			}
			++stepCount;
		}

		return stepCount;
	}
}  // namespace collatz_conjecture
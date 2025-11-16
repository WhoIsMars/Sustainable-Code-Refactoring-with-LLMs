#include "collatz_conjecture.h"

#include <stdexcept>

namespace collatz_conjecture {
	int steps(int n) {
		if (n <= 0) throw std::domain_error("Argument must be greater than zero.");

		int stepCount = 0;

		while (n != 1) {
			if ((n & 1) == 0) {
				n >>= 1;
			} else {
				if (n > (INT_MAX - 1) / 3) {
					throw std::overflow_error("Potential overflow detected");
				}
				n = 3 * n + 1;
			}
			++stepCount;
		}

		return stepCount;
	}
}  // namespace collatz_conjecture
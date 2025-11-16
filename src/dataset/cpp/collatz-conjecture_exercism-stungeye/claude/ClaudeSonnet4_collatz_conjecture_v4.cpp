#include "collatz_conjecture.h"

#include <stdexcept>

namespace collatz_conjecture {
	int steps(int n) {
		if (n <= 0) throw std::domain_error("Argument must be greater than zero.");

		int stepCount = 0;

		while (n != 1) {
			if (n & 1) {
				n = n * 3 + 1;
			} else {
				n >>= 1;
			}
			++stepCount;
		}

		return stepCount;
	}
}  // namespace collatz_conjecture
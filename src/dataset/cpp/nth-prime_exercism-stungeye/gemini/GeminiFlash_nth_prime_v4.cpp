#include "nth_prime.h"
#include <cmath>
#include <limits>
#include <stdexcept>
#include <vector>

namespace nth_prime {

	int nth(int n) {
		if (n <= 0) throw std::domain_error("There is no non-positive prime number");

		if (n <= 6) {
			int small_primes[] = {2, 3, 5, 7, 11, 13};
			return small_primes[n - 1];
		}

		// Estimate the upper bound for the nth prime number.  This is a loose bound.
		int upper_bound = n * (static_cast<int>(log(n)) + static_cast<int>(log(log(n))));
		if (upper_bound < 0) upper_bound = std::numeric_limits<int>::max() / 2; // Handle potential overflow

		std::vector<bool> sieve(upper_bound + 1, true);
		sieve[0] = sieve[1] = false;

		int count = 0;
		for (int p = 2; p <= upper_bound; ++p) {
			if (sieve[p]) {
				++count;
				if (count == n) return p;

				// Mark multiples of p as non-prime, starting from p*p.
				// Optimization: Start from p*p because smaller multiples are already marked.
				if (static_cast<long long>(p) * p <= upper_bound) { // Prevent overflow
					for (long long i = static_cast<long long>(p) * p; i <= upper_bound; i += p) {
						sieve[i] = false;
					}
				}
			}
		}

		throw std::domain_error("Prime not found within estimated range.");
	}
} // namespace nth_prime
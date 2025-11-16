#include "nth_prime.h"
#include <cmath>
#include <stdexcept>
#include <vector>

namespace nth_prime {

	int nth(int n) {
		if (n <= 0) {
			throw std::domain_error("There is no 0th prime number");
		}

		if (n <= 6) {
			int small_primes[] = { 2, 3, 5, 7, 11, 13 };
			return small_primes[n - 1];
		}

		// Estimate upper bound for the nth prime number.  This avoids unnecessary iterations.
		int upper_bound = n * (static_cast<int>(log(n)) + static_cast<int>(log(log(n))));
		if (upper_bound < 0) upper_bound = 1000000; // handle overflow for very large n

		std::vector<bool> sieve(upper_bound + 1, true);
		sieve[0] = sieve[1] = false;

		int count = 0;
		for (int p = 2; p <= upper_bound; ++p) {
			if (sieve[p]) {
				++count;
				if (count == n) {
					return p;
				}

				// Mark multiples of p as non-prime, starting from p*p.
				// Optimization: start from p*p because smaller multiples are already marked.
				if (static_cast<long long>(p) * p <= upper_bound) {
					for (long long i = static_cast<long long>(p) * p; i <= upper_bound; i += p) {
						sieve[i] = false;
					}
				}
			}
		}

		throw std::domain_error("Prime not found within estimated range.");
	}
} // namespace nth_prime
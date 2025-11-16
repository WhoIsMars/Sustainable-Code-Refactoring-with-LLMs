#include "nth_prime.h"
#include <cmath>
#include <stdexcept>
#include <vector>

namespace nth_prime {

	int nth(int n) {
		if (n <= 0) {
			throw std::domain_error("There is no nth prime for n <= 0");
		}

		if (n <= 6) {
			constexpr int small_primes[] = {2, 3, 5, 7, 11, 13};
			return small_primes[n - 1];
		}

		// Use a sieve to generate primes up to a reasonable limit.
		// A good upper bound for the nth prime is n * log(n) + n * log(log(n)) for larger n
		// We add a bit of margin to be safe.
		int upper_bound = static_cast<int>(n * (std::log(n) + std::log(std::log(n))));
		if (upper_bound < 0) {
			//Handle overflow, use a larger upper bound
			upper_bound = 1000000;
		}
		upper_bound = std::max(upper_bound, 100); // Ensure a minimum size

		std::vector<bool> is_prime(upper_bound + 1, true);
		is_prime[0] = is_prime[1] = false;

		for (int p = 2; p * p <= upper_bound; ++p) {
			if (is_prime[p]) {
				for (int i = p * p; i <= upper_bound; i += p) {
					is_prime[i] = false;
				}
			}
		}

		int count = 0;
		for (int p = 2; p <= upper_bound; ++p) {
			if (is_prime[p]) {
				++count;
				if (count == n) {
					return p;
				}
			}
		}

		// If we reach here, the upper bound was not large enough.  This is *very* unlikely
		// given the upper bound calculation, but we handle it anyway.  We could throw an
		// exception, or we could extend the sieve.  For simplicity, we throw an exception.
		throw std::domain_error("Upper bound for prime generation was insufficient.");
	}
} // namespace nth_prime
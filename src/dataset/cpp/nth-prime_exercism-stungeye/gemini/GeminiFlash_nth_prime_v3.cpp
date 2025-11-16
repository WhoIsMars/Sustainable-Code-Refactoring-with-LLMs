#include "nth_prime.h"
#include <cmath>
#include <limits>
#include <stdexcept>
#include <vector>

namespace nth_prime {

	int nth(int n) {
		if (n <= 0) throw std::domain_error("There is no non-positive prime number");

		if (n <= 6) {
			const int small_primes[] = {2, 3, 5, 7, 11, 13};
			return small_primes[n - 1];
		}

		// Estimate the upper bound for the nth prime using the prime number theorem
		int upper_bound = static_cast<int>(n * (std::log(n) + std::log(std::log(n))));
		if (upper_bound < 0) upper_bound = std::numeric_limits<int>::max() / 2; // Handle potential overflow

		std::vector<bool> sieve(upper_bound + 1, true);
		sieve[0] = sieve[1] = false;

		for (int p = 2; p * p <= upper_bound; ++p) {
			if (sieve[p]) {
				for (int i = p * p; i <= upper_bound; i += p) {
					sieve[i] = false;
				}
			}
		}

		int count = 0;
		for (int i = 2; i <= upper_bound; ++i) {
			if (sieve[i]) {
				++count;
				if (count == n) return i;
			}
		}

		throw std::domain_error("Failed to find the nth prime within the estimated range.");
	}

	bool isPrime(int n) {
		if (n <= 1) return false;
		if (n <= 3) return true;
		if (n % 2 == 0 || n % 3 == 0) return false;

		for (int i = 5; i * i <= n; i = i + 6) {
			if (n % i == 0 || n % (i + 2) == 0)
				return false;
		}

		return true;
	}
} // namespace nth_prime
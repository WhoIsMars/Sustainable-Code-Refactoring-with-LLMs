#include "nth_prime.h"
#include <cmath>
#include <vector>
#include <stdexcept>

namespace nth_prime {

	int nth(int n) {
		if (n <= 0) throw std::domain_error("There is no 0th prime number");

		std::vector<int> primes;
		primes.reserve(n);
		primes.push_back(2);

		for (int candidate = 3; primes.size() < static_cast<size_t>(n); candidate += 2) {
			bool is_prime = true;
			int limit = static_cast<int>(std::sqrt(candidate));
			for (int prime : primes) {
				if (prime > limit) break;
				if (candidate % prime == 0) {
					is_prime = false;
					break;
				}
			}
			if (is_prime) primes.push_back(candidate);
		}

		return primes[n - 1];
	}

} // namespace nth_prime
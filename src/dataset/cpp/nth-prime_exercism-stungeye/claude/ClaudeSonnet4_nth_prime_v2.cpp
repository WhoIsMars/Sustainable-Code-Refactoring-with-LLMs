#include "nth_prime.h"
#include <cmath>
#include <limits>
#include <stdexcept>
#include <vector>

namespace nth_prime {

	int nth(int n) {
		if (n == 0) throw std::domain_error("There is no 0th prime number");
		if (n == 1) return 2;

		std::vector<bool> sieve(100000, true);
		sieve[0] = sieve[1] = false;
		
		int limit = static_cast<int>(std::sqrt(100000));
		for (int i = 2; i <= limit; ++i) {
			if (sieve[i]) {
				for (int j = i * i; j < 100000; j += i) {
					sieve[j] = false;
				}
			}
		}

		int count = 0;
		for (int i = 2; i < 100000; ++i) {
			if (sieve[i]) {
				++count;
				if (count == n) return i;
			}
		}

		// Fallback for larger primes
		for (int i = 100000, count_fallback = count; i < std::numeric_limits<int>::max(); i++) {
			if (isPrime(i)) ++count_fallback;
			if (count_fallback == n) return i;
		}

		throw std::domain_error("Ran out of prime candidates in the integer range.");
	}

	bool isPrime(int n) {
		if (n < 2) return false;
		if (n == 2) return true;
		if (n % 2 == 0) return false;

		const int maxRelevantDivisor = static_cast<int>(std::sqrt(n));
		for (int i = 3; i <= maxRelevantDivisor; i += 2) {
			if (n % i == 0) return false;
		}

		return true;
	}
} // namespace nth_prime
#include "nth_prime.h"
#include <cmath>
#include <limits>
#include <stdexcept>
#include <vector>

namespace nth_prime {

	int nth(int n) {
		if (n == 0) throw std::domain_error("There is no 0th prime number");
		if (n == 1) return 2;
		if (n == 2) return 3;

		std::vector<int> primes;
		primes.reserve(n);
		primes.push_back(2);
		primes.push_back(3);

		int candidate = 5;
		while (primes.size() < n) {
			if (isPrimeOptimized(candidate, primes)) {
				primes.push_back(candidate);
			}
			candidate += 2;
		}

		return primes[n - 1];
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

	bool isPrimeOptimized(int n, const std::vector<int>& knownPrimes) {
		const int maxRelevantDivisor = static_cast<int>(std::sqrt(n));
		
		for (int prime : knownPrimes) {
			if (prime > maxRelevantDivisor) break;
			if (n % prime == 0) return false;
		}

		return true;
	}

} // namespace nth_prime
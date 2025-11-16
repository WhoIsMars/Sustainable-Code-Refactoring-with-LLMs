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

		std::vector<bool> sieve(100000, true);
		sieve[0] = sieve[1] = false;
		
		int count = 0;
		int limit = 100000;
		
		while (true) {
			for (int i = 2; i * i < limit; ++i) {
				if (sieve[i]) {
					for (int j = i * i; j < limit; j += i) {
						sieve[j] = false;
					}
				}
			}
			
			for (int i = 2; i < limit; ++i) {
				if (sieve[i]) {
					++count;
					if (count == n) return i;
				}
			}
			
			if (limit >= std::numeric_limits<int>::max() / 2) {
				throw std::domain_error("Ran out of prime candidates in the integer range.");
			}
			
			int old_limit = limit;
			limit *= 2;
			sieve.resize(limit, true);
			
			for (int i = 2; i * i < limit; ++i) {
				if (sieve[i]) {
					int start = std::max(i * i, (old_limit + i - 1) / i * i);
					for (int j = start; j < limit; j += i) {
						sieve[j] = false;
					}
				}
			}
		}
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
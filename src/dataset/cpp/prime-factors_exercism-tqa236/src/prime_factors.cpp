#include "prime_factors.h"

#include <cmath>

std::vector<int> prime_factors::primes(int number) {
  std::vector<int> primes;
  std::vector<bool> is_prime(number + 1, 1);
  for (int i = 2; i <= number; i++) {
    if (is_prime[i]) {
      primes.push_back(i);
      for (int j = 2 * i; j <= number; j += i) {
        is_prime[j] = 0;
      }
    }
  }
  return primes;
}

std::vector<int> prime_factors::of(int number) {
  std::vector<int> factors;
  std::vector<int> primes =
      prime_factors::primes(static_cast<int>(std::sqrt(number)) + 1);
  for (auto prime : primes) {
    while (number % prime == 0) {
      factors.push_back(prime);
      number = number / prime;
    }
  }
  if (number > 1) {
    factors.push_back(number);
  }
  return factors;
}

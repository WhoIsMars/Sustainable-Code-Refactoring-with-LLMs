#include "prime_factors.h"

#include <cmath>
#include <vector>

std::vector<int> prime_factors::primes(int number) {
  std::vector<int> primes;
  if (number < 2) return primes;

  std::vector<bool> is_prime(number + 1, true);
  is_prime[0] = is_prime[1] = false;

  for (int p = 2; p * p <= number; ++p) {
    if (is_prime[p]) {
      for (int i = p * p; i <= number; i += p) {
        is_prime[i] = false;
      }
    }
  }

  for (int p = 2; p <= number; ++p) {
    if (is_prime[p]) {
      primes.push_back(p);
    }
  }
  return primes;
}

std::vector<int> prime_factors::of(int number) {
  std::vector<int> factors;
  if (number <= 1) return factors;

  int n = number;
  for (int i = 2; i * i <= n; ++i) {
    while (n % i == 0) {
      factors.push_back(i);
      n /= i;
    }
  }

  if (n > 1) {
    factors.push_back(n);
  }

  return factors;
}
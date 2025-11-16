#include "prime_factors.h"

#include <cmath>
#include <vector>

std::vector<int> prime_factors::primes(int number) {
  std::vector<int> primes;
  if (number < 2) return primes;

  std::vector<bool> is_prime(number + 1, true);
  is_prime[0] = is_prime[1] = false;

  for (int i = 2; i * i <= number; ++i) {
    if (is_prime[i]) {
      for (int j = i * i; j <= number; j += i) {
        is_prime[j] = false;
      }
    }
  }

  for (int i = 2; i <= number; ++i) {
    if (is_prime[i]) {
      primes.push_back(i);
    }
  }

  return primes;
}

std::vector<int> prime_factors::of(int number) {
  std::vector<int> factors;
  if (number < 2) return factors;

  for (int i = 2; i * i <= number; ++i) {
    while (number % i == 0) {
      factors.push_back(i);
      number /= i;
    }
  }

  if (number > 1) {
    factors.push_back(number);
  }

  return factors;
}
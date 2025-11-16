#include "prime_factors.h"

#include <cmath>
#include <vector>

std::vector<int> prime_factors::primes(int number) {
  if (number < 2) {
    return {};
  }

  std::vector<int> primes;
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

  while (number % 2 == 0) {
    factors.push_back(2);
    number /= 2;
  }

  for (int i = 3; i * i <= number; i += 2) {
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
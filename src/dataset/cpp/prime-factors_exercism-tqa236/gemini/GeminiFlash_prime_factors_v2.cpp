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

  while (number % 2 == 0) {
    factors.push_back(2);
    number /= 2;
  }

  if (number == 1) return factors;

  int limit = static_cast<int>(std::sqrt(number)) + 1;
  std::vector<int> primes_up_to_sqrt = prime_factors::primes(limit);

  for (int prime : primes_up_to_sqrt) {
    while (number % prime == 0) {
      factors.push_back(prime);
      number /= prime;
    }
    if (number == 1) return factors;
  }

  if (number > 1) {
    factors.push_back(number);
  }

  return factors;
}
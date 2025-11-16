#include "prime_factors.h"

#include <cmath>
#include <vector>

std::vector<int> prime_factors::primes(int number) {
  std::vector<int> primes_list;
  if (number < 2) {
    return primes_list;
  }

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
      primes_list.push_back(p);
    }
  }
  return primes_list;
}

std::vector<int> prime_factors::of(int number) {
  std::vector<int> factors;
  if (number <= 1) {
    return factors;
  }

  int n = number;
  std::vector<int> primes_list =
      prime_factors::primes(static_cast<int>(std::sqrt(n)) + 1);

  for (int prime : primes_list) {
    while (n % prime == 0) {
      factors.push_back(prime);
      n /= prime;
    }
    if (n == 1) break;
  }

  if (n > 1) {
    factors.push_back(n);
  }

  return factors;
}
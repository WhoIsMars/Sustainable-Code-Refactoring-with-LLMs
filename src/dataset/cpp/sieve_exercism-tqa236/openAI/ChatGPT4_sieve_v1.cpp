#include "sieve.h"

#include <vector>

namespace sieve {
vector<int> primes(int number) {
  if (number < 2) return {};

  vector<bool> is_prime(number + 1, true);
  is_prime[0] = is_prime[1] = false;
  vector<int> primes;

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
}  // namespace sieve
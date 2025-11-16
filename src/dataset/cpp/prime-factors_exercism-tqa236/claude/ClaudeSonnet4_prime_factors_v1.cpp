#include "prime_factors.h"

#include <cmath>

std::vector<int> prime_factors::primes(int number) {
  if (number < 2) return {};
  
  std::vector<int> primes;
  primes.reserve(number / (std::log(number) - 1)); // Approximate prime count
  
  std::vector<bool> is_prime(number + 1, true);
  is_prime[0] = is_prime[1] = false;
  
  for (int i = 2; i * i <= number; i++) {
    if (is_prime[i]) {
      for (int j = i * i; j <= number; j += i) {
        is_prime[j] = false;
      }
    }
  }
  
  for (int i = 2; i <= number; i++) {
    if (is_prime[i]) {
      primes.push_back(i);
    }
  }
  
  return primes;
}

std::vector<int> prime_factors::of(int number) {
  if (number <= 1) return {};
  
  std::vector<int> factors;
  
  // Handle factor 2 separately
  while (number % 2 == 0) {
    factors.push_back(2);
    number /= 2;
  }
  
  // Check odd factors up to sqrt(number)
  for (int i = 3; i * i <= number; i += 2) {
    while (number % i == 0) {
      factors.push_back(i);
      number /= i;
    }
  }
  
  // If number is still > 1, it's a prime factor
  if (number > 1) {
    factors.push_back(number);
  }
  
  return factors;
}
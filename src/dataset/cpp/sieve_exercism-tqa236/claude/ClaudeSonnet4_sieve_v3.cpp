#include "sieve.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;
namespace sieve {
vector<int> primes(int number) {
  if (number < 2) {
    return vector<int>();
  }
  
  vector<bool> is_prime(number + 1, true);
  is_prime[0] = is_prime[1] = false;
  
  vector<int> result;
  result.reserve(number / (log(number) > 0 ? log(number) : 1));
  
  for (int i = 2; i * i <= number; ++i) {
    if (is_prime[i]) {
      for (int j = i * i; j <= number; j += i) {
        is_prime[j] = false;
      }
    }
  }
  
  for (int i = 2; i <= number; ++i) {
    if (is_prime[i]) {
      result.push_back(i);
    }
  }
  
  return result;
}
}  // namespace sieve
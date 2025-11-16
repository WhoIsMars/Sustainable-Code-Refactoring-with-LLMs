#include "sieve.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;
namespace sieve {
vector<int> primes(int number) {
  vector<int> primes;
  vector<int> numbers;
  for (int i = 1; i <= number; i++) {
    numbers.push_back(i);
  }
  for (int i = 2; i <= number; i++) {
    if (numbers[i - 1] != 0) {
      primes.push_back(numbers[i - 1]);
      for (int j = 2 * numbers[i - 1]; j <= number; j += numbers[i - 1]) {
        numbers[j - 1] = 0;
      }
    }
  }
  return primes;
}
}  // namespace sieve

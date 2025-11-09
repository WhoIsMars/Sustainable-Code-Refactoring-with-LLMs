#include "armstrong_numbers.h"
#include <cmath>
#include <numeric>
#include <vector>

namespace armstrong_numbers {

bool is_armstrong_number(int number) {
  if (number < 0) {
    return false;
  }

  if (number == 0) {
    return true;
  }

  std::vector<int> digits;
  int temp = number;
  while (temp > 0) {
    digits.push_back(temp % 10);
    temp /= 10;
  }

  int num_digits = digits.size();

  long long sum = 0;
  for (int digit : digits) {
    long long power = 1;
    for (int i = 0; i < num_digits; ++i) {
      power *= digit;
    }
    sum += power;

    if (sum > number) return false;
  }

  return sum == number;
}

} // namespace armstrong_numbers
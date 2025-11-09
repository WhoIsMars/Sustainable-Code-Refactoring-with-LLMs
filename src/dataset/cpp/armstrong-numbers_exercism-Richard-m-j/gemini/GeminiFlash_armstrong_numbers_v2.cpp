#include "armstrong_numbers.h"
#include <cmath>
#include <numeric>
#include <string>

using namespace std;

namespace armstrong_numbers {

bool is_armstrong_number(int number) {
  if (number < 0) {
    return false;
  }

  string num_str = to_string(number);
  int num_digits = num_str.length();

  long sum = 0;
  for (char c : num_str) {
    int digit = c - '0';
    sum += round(pow(digit, num_digits)); 
    if (sum > number) return false; // Early exit optimization
  }

  return sum == number;
}

}  // namespace armstrong_numbers
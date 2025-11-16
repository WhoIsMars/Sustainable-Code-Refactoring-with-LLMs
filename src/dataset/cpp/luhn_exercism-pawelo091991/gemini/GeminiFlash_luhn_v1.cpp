#include "luhn.h"
#include <string>
#include <algorithm>
#include <cctype>

using std::string;

bool luhn::valid(string str) {
  // Remove spaces efficiently using a single pass.
  str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());

  // Early exit for strings with length <= 1.
  if (str.length() <= 1) {
    return false;
  }

  int sum = 0;
  bool double_digit = false;

  // Iterate in reverse using iterators for potential performance gains.
  for (auto it = str.rbegin(); it != str.rend(); ++it) {
    if (!isdigit(*it)) {
      return false;
    }

    int digit = *it - '0';

    if (double_digit) {
      digit *= 2;
      if (digit > 9) {
        digit -= 9;
      }
    }

    sum += digit;
    double_digit = !double_digit;
  }

  return (sum % 10 == 0);
}
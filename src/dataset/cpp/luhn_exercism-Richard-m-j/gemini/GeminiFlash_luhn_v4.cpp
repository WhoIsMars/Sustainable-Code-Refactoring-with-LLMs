#include "luhn.h"
#include <string>

namespace luhn {
bool valid(std::string inputNumber) {
  int sum = 0;
  int length = 0;

  for (char c : inputNumber) {
    if (c != ' ') {
      if (!isdigit(c)) {
        return false;
      }
      length++;
    }
  }

  if (length <= 1) {
    return false;
  }

  bool doubleDigit = false;
  for (int i = inputNumber.length() - 1; i >= 0; --i) {
    if (inputNumber[i] != ' ') {
      int digit = inputNumber[i] - '0';
      if (doubleDigit) {
        digit *= 2;
        if (digit > 9) {
          digit -= 9;
        }
      }
      sum += digit;
      doubleDigit = !doubleDigit;
    }
  }

  return (sum % 10 == 0);
}
} // namespace luhn
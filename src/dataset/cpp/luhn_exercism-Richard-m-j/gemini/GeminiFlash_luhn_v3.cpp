#include "luhn.h"
#include <string>

namespace luhn {

bool valid(std::string inputNumber) {
  int sum = 0;
  int length = 0;

  for (int i = 0; i < inputNumber.length(); ++i) {
    if (inputNumber[i] != ' ') {
      if (!isdigit(inputNumber[i])) {
        return false;
      }
      inputNumber[length++] = inputNumber[i];
    }
  }

  if (length <= 1) {
    return false;
  }

  for (int i = length - 1, j = 1; i >= 0; --i, ++j) {
    int digit = inputNumber[i] - '0';
    if (j % 2 == 0) {
      digit *= 2;
      if (digit > 9) {
        digit -= 9;
      }
    }
    sum += digit;
  }

  return (sum % 10 == 0);
}

} // namespace luhn
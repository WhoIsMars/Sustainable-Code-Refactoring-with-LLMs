#include "luhn.h"
#include <string>

namespace luhn {
bool valid(std::string inputNumber) {
  int sum = 0;
  int length = 0;
  bool alt = false;

  for (int i = inputNumber.length() - 1; i >= 0; --i) {
    if (inputNumber[i] == ' ') continue;

    if (!isdigit(inputNumber[i])) return false;

    int digit = inputNumber[i] - '0';

    if (alt) {
      digit *= 2;
      if (digit > 9) digit -= 9;
    }

    sum += digit;
    alt = !alt;
    length++;
  }

  return (length > 1) && (sum % 10 == 0);
}
} // namespace luhn
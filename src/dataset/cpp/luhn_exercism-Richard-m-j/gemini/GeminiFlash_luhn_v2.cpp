#include "luhn.h"
#include <string>

namespace luhn {
bool valid(std::string inputNumber) {
  int sum = 0;
  int length = 0;

  // Pre-allocate space to avoid reallocations
  inputNumber.erase(std::remove(inputNumber.begin(), inputNumber.end(), ' '), inputNumber.end());
  length = static_cast<int>(inputNumber.length());

  if (length <= 1) return false;

  for (int i = length - 1; i >= 0; --i) {
    if (!isdigit(inputNumber[i])) return false;

    int digit = inputNumber[i] - '0';
    if ((length - 1 - i) % 2 != 0) {
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
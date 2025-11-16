#include <algorithm>
#include <stdexcept>
#include <vector>

#include "all_your_base.h"

namespace all_your_base {
unsigned int toDecimalNumber(unsigned int fromBase,
                             const std::vector<unsigned int>& digits) {
  if (fromBase < 2) {
    throw std::invalid_argument("Input base must be 2 or greater.");
  }

  unsigned int num = 0;
  for (unsigned int digit : digits) {
    if (digit >= fromBase) {
      throw std::invalid_argument(
          "Input digits cannot be equal or greater than input base.");
    }
    if (num > (UINT_MAX / fromBase)) {
      throw std::overflow_error("Overflow during base conversion.");
    }
    num *= fromBase;
    if (num > (UINT_MAX - digit)) {
      throw std::overflow_error("Overflow during base conversion.");
    }
    num += digit;
  }
  return num;
}

std::vector<unsigned int> fromDecimalNumber(unsigned int decimalNumber,
                                            unsigned int toBase) {
  if (toBase < 2) {
    throw std::invalid_argument("Output base must be 2 or greater.");
  }

  if (decimalNumber == 0) {
    return {0};
  }

  std::vector<unsigned int> digits;
  digits.reserve(32); 

  while (decimalNumber != 0) {
    digits.push_back(decimalNumber % toBase);
    decimalNumber /= toBase;
  }

  std::reverse(digits.begin(), digits.end());
  return digits;
}

std::vector<unsigned int> convert(unsigned int fromBase,
                                  const std::vector<unsigned int>& digits,
                                  unsigned int toBase) {
  if (fromBase < 2) {
    throw std::invalid_argument("Input base must be 2 or greater.");
  }
  if (toBase < 2) {
    throw std::invalid_argument("Output base must be 2 or greater.");
  }

  if (digits.empty()) {
    return {0};
  }

  return fromDecimalNumber(toDecimalNumber(fromBase, digits), toBase);
}
}  // namespace all_your_base
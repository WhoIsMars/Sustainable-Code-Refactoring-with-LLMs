#include "all_your_base.h"

#include <algorithm>
#include <stdexcept>
#include <vector>
#include <numeric>

using std::invalid_argument;
using std::vector;

namespace all_your_base {
vector<unsigned int> convert(int in_base, vector<unsigned int> in_digits,
                             int out_base) {
  if ((in_base <= 1) || (out_base <= 1)) {
    throw invalid_argument("Invalid base.");
  }

  if (in_digits.empty()) {
    return {};
  }

  if (std::any_of(in_digits.begin(), in_digits.end(),
                  [&](unsigned int digit) { return digit >= (unsigned int)in_base; })) {
    throw invalid_argument("Invalid digit(s) for the given input base.");
  }

  unsigned int dec_num = 0;
  for (unsigned int digit : in_digits) {
    if (dec_num > UINT_MAX / in_base || digit > UINT_MAX - in_base * dec_num) {
      throw invalid_argument("Input number too large for unsigned int.");
    }
    dec_num = dec_num * in_base + digit;
  }

  vector<unsigned int> out_digits;
  if (dec_num == 0) {
    return {0};
  }

  while (dec_num > 0) {
    out_digits.push_back(dec_num % out_base);
    dec_num /= out_base;
  }

  std::reverse(out_digits.begin(), out_digits.end());
  return out_digits;
}
}  // namespace all_your_base
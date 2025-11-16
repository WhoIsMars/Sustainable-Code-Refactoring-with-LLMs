#include "all_your_base.h"

#include <stdexcept>
#include <vector>

using std::invalid_argument;
using std::vector;

namespace all_your_base {
vector<unsigned int> convert(int in_base, const vector<unsigned int>& in_digits,
                             int out_base) {
  if (in_base <= 1 || out_base <= 1) {
    throw invalid_argument("Invalid base.");
  }
  if (in_digits.empty()) return {};
  for (const auto& digit : in_digits) {
    if (digit >= static_cast<unsigned int>(in_base)) {
      throw invalid_argument("Invalid base.");
    }
  }

  int dec_num = 0;
  for (const auto& digit : in_digits) {
    dec_num = dec_num * in_base + digit;
  }

  if (dec_num == 0) return {0};

  vector<unsigned int> out_digits;
  while (dec_num > 0) {
    out_digits.push_back(dec_num % out_base);
    dec_num /= out_base;
  }
  std::reverse(out_digits.begin(), out_digits.end());
  return out_digits;
}
}  // namespace all_your_base
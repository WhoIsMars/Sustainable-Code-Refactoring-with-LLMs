#include "all_your_base.h"

#include <algorithm>
#include <stdexcept>
#include <vector>

using std::invalid_argument;
using std::vector;

namespace all_your_base {
vector<unsigned int> convert(int in_base, vector<unsigned int> in_digits,
                             int out_base) {
  if ((in_base <= 1) || (out_base <= 1)) {
    throw invalid_argument("Invalid base.");
  }
  if (in_digits.empty()) return {};
  
  for (const auto& digit : in_digits) {
    if (digit >= static_cast<unsigned int>(in_base)) {
      throw invalid_argument("Invalid base.");
    }
  }

  int dec_num = to_dec(in_base, in_digits);
  return to_base(dec_num, out_base);
}

int to_dec(int in_base, vector<unsigned int> in_digits) {
  int dec_num = 0;
  for (const auto& digit : in_digits) {
    dec_num = digit + in_base * dec_num;
  }
  return dec_num;
}

vector<unsigned int> to_base(int dec_num, int out_base) {
  if (dec_num == 0) return {0};
  
  vector<unsigned int> out_digits;
  out_digits.reserve(32);
  
  while (dec_num != 0) {
    out_digits.push_back(dec_num % out_base);
    dec_num /= out_base;
  }
  
  std::reverse(out_digits.begin(), out_digits.end());
  return out_digits;
}
}  // namespace all_your_base
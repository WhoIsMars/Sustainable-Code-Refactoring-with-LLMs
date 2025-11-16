#include "all_your_base.h"

#include <algorithm>
#include <stdexcept>
#include <vector>

using std::invalid_argument;
using std::max_element;
using std::vector;

namespace all_your_base {
vector<unsigned int> convert(int in_base, vector<unsigned int> in_digits,
                             int out_base) {
  if ((in_base <= 1) || (out_base <= 1)) {
    throw invalid_argument("Invalid base.");
  }
  if (in_digits.size() == 0) return {};
  if (*max_element(std::begin(in_digits), std::end(in_digits)) >=
      (unsigned int)in_base) {
    throw invalid_argument("Invalid base.");
  }

  int dec_num = to_dec(in_base, in_digits);
  vector<unsigned int> out_digits = to_base(dec_num, out_base);
  return out_digits;
}

int to_dec(int in_base, vector<unsigned int> in_digits) {
  int dec_num = 0;
  for (auto const& digit : in_digits) {
    dec_num = digit + in_base * dec_num;
  }
  return dec_num;
}

vector<unsigned int> to_base(int dec_num, int out_base) {
  vector<unsigned int> out_digits;
  while (dec_num != 0) {
    out_digits.insert(out_digits.begin(), dec_num % out_base);
    dec_num = dec_num / out_base;
  }
  return out_digits;
}
}  // namespace all_your_base

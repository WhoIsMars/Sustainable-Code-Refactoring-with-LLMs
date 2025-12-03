#include "reverse_string.h"
#include <algorithm>

namespace reverse_string {

string reverse_string(string str) {
  if (str.size() <= 1) {
    return str;
  }
  
  const size_t len = str.size();
  const size_t half_len = len / 2;
  
  for (size_t i = 0; i < half_len; ++i) {
    std::swap(str[i], str[len - 1 - i]);
  }
  
  return str;
}

} // namespace reverse_string
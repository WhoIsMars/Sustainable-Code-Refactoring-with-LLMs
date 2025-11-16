#include "reverse_string.h"
#include <string>

namespace reverse_string {

string reverse_string(string str) {
  size_t n = str.length();
  for (size_t i = 0; i < n / 2; ++i) {
    std::swap(str[i], str[n - i - 1]);
  }
  return str;
}

} // namespace reverse_string
#include <iostream>
#include <string>
#include <algorithm>

namespace binary {
int convert(const std::string& bin) {
  int dec = 0;
  size_t l = bin.length();

  for (size_t i = 0; i < l; ++i) {
    char c = bin[i];
    if (c == '0') {
      dec <<= 1; // Equivalent to dec = dec * 2, but faster
    } else if (c == '1') {
      dec = (dec << 1) | 1; // Equivalent to dec = dec * 2 + 1, but faster
    } else {
      return 0;
    }
  }
  return dec;
}
}  // namespace binary
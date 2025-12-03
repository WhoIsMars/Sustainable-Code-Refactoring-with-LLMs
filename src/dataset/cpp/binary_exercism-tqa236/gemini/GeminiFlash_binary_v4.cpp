#include <iostream>
#include <string>
#include <algorithm>

namespace binary {
int convert(std::string bin) {
  int dec = 0;
  size_t l = bin.length();
  for (size_t i = 0; i < l; ++i) {
    char c = bin[i];
    if (c != '0' && c != '1') {
      return 0;
    }
    dec = (dec << 1) | (c - '0');
  }
  return dec;
}
}  // namespace binary
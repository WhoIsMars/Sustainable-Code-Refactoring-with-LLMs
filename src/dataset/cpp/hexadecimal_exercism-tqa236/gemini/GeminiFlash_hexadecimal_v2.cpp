#include <iostream>
#include <string>

namespace hexadecimal {
int convert(const std::string& hex) {
  int dec = 0;
  size_t l = hex.length();
  for (size_t i = 0; i < l; ++i) {
    char c = hex[i];
    int num;
    if (c >= '0' && c <= '9') {
      num = c - '0';
    } else if (c >= 'a' && c <= 'f') {
      num = c - 'a' + 10;
    } else if (c >= 'A' && c <= 'F') {
        num = c - 'A' + 10;
    }
    else {
      return 0;
    }
    if (dec > (INT_MAX - num) / 16) return 0; // Check for overflow before multiplication
    dec = (dec << 4) | num; // Equivalent to dec = 16 * dec + num, but faster
  }
  return dec;
}
}  // namespace hexadecimal
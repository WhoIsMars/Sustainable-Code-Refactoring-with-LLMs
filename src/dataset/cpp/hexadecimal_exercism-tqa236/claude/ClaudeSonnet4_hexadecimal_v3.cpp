#include <iostream>
using namespace std;

namespace hexadecimal {
int convert(const string& hex) {
  int dec = 0;
  for (char c : hex) {
    int digit;
    if (c >= '0' && c <= '9') {
      digit = c - '0';
    } else if (c >= 'a' && c <= 'f') {
      digit = c - 'a' + 10;
    } else if (c >= 'A' && c <= 'F') {
      digit = c - 'A' + 10;
    } else {
      return 0;
    }
    dec = (dec << 4) + digit;
  }
  return dec;
}
}  // namespace hexadecimal
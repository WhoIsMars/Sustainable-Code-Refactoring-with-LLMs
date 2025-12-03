#include <iostream>
using namespace std;

namespace hexadecimal {
int convert(const string& hex) {
  int dec = 0;
  for (char c : hex) {
    int num;
    if (c >= '0' && c <= '9') {
      num = c - '0';
    } else if (c >= 'a' && c <= 'f') {
      num = c - 'a' + 10;
    } else {
      return 0;
    }
    dec = (dec << 4) + num; // Use bitwise shift for efficiency
  }
  return dec;
}
}  // namespace hexadecimal
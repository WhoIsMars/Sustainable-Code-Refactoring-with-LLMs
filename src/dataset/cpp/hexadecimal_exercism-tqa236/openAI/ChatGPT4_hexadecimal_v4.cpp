#include <iostream>
#include <cctype>
using namespace std;

namespace hexadecimal {
int convert(const string& hex) {
  int dec = 0;
  for (char c : hex) {
    int num;
    if (isdigit(c)) {
      num = c - '0';
    } else if (c >= 'a' && c <= 'f') {
      num = c - 'a' + 10;
    } else {
      return 0;
    }
    dec = (dec << 4) + num; // Multiply by 16 using bitwise shift
  }
  return dec;
}
}  // namespace hexadecimal
#include <iostream>
#include <cctype>
using namespace std;

namespace hexadecimal {
int convert(const string& hex) {
  int dec = 0;
  for (char ch : hex) {
    int num;
    if (isdigit(ch)) {
      num = ch - '0';
    } else if (ch >= 'a' && ch <= 'f') {
      num = ch - 'a' + 10;
    } else {
      return 0;
    }
    dec = (dec << 4) + num; // Multiply by 16 using bitwise shift
  }
  return dec;
}
}  // namespace hexadecimal
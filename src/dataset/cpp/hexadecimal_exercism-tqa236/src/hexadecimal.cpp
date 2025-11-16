#include <iostream>
using namespace std;

namespace hexadecimal {
int convert(string hex) {
  int dec = 0;
  int l = hex.length();
  for (int i = 0; i < l; i++) {
    int num = (int)hex[i];
    if ((num >= 48) && (num <= 57)) {
      num = num - (int)'0';
    } else {
      if ((num >= 97) && (num <= 102)) {
        num = num - (int)'a' + 10;
      } else
        return 0;
    }
    dec = 16 * dec + num;
  }
  return dec;
}
}  // namespace hexadecimal

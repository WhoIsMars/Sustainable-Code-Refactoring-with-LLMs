#include <iostream>
using namespace std;

namespace binary {
int convert(string bin) {
  int dec = 0;
  int l = bin.length();
  for (int i = 0; i < l; i++) {
    int num = (int)bin[i];
    if ((num >= 48) && (num <= 49)) {
      num = num - (int)'0';
    } else
      return 0;
    dec = 2 * dec + num;
  }
  return dec;
}
}  // namespace binary

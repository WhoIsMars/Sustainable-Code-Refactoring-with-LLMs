#include <iostream>
using namespace std;

namespace binary {
int convert(const string& bin) {
  int dec = 0;
  const int l = bin.length();
  
  for (int i = 0; i < l; i++) {
    const char c = bin[i];
    if (c == '0') {
      dec <<= 1;
    } else if (c == '1') {
      dec = (dec << 1) | 1;
    } else {
      return 0;
    }
  }
  return dec;
}
}  // namespace binary
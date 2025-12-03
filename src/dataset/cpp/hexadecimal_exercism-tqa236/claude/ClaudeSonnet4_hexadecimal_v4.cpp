#include <iostream>
using namespace std;

namespace hexadecimal {
int convert(string hex) {
  int dec = 0;
  const int length = hex.length();
  
  for (int i = 0; i < length; ++i) {
    const char c = hex[i];
    int digit;
    
    if (c >= '0' && c <= '9') {
      digit = c - '0';
    } else if (c >= 'a' && c <= 'f') {
      digit = c - 'a' + 10;
    } else {
      return 0;
    }
    
    dec = (dec << 4) + digit;
  }
  
  return dec;
}
}  // namespace hexadecimal
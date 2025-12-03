#include <iostream>
#include <string>
using namespace std;

namespace binary {
int convert(const string& bin) {
  int dec = 0;
  for (char c : bin) {
    if (c == '0' || c == '1') {
      dec = (dec << 1) | (c - '0');
    } else {
      return 0;
    }
  }
  return dec;
}
}  // namespace binary
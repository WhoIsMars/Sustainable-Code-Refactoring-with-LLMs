#include <iostream>
using namespace std;

namespace binary {
int convert(const string& bin) {
  int dec = 0;
  for (char ch : bin) {
    if (ch == '0' || ch == '1') {
      dec = (dec << 1) | (ch - '0');
    } else {
      return 0;
    }
  }
  return dec;
}
}  // namespace binary
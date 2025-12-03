#include <iostream>
using namespace std;

namespace binary {
int convert(const string& bin) {
  int dec = 0;
  for (char c : bin) {
    if (c < '0' || c > '1') {
      return 0;
    }
    dec = (dec << 1) + (c - '0');
  }
  return dec;
}
}  // namespace binary
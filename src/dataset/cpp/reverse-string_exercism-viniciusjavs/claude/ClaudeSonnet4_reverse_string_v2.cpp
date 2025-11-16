#include "reverse_string.h"
#include <algorithm>

namespace reverse_string {

string reverse_string(string str) {
  if (str.size() <= 1) return str;
  
  size_t left = 0;
  size_t right = str.size() - 1;
  
  while (left < right) {
    char temp = str[left];
    str[left] = str[right];
    str[right] = temp;
    ++left;
    --right;
  }
  
  return str;
}

} // namespace reverse_string
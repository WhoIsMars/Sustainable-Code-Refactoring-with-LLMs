#include "reverse_string.h"
#include <algorithm>

namespace reverse_string {

string reverse_string(string str) {
  if (str.size() <= 1) return str;
  
  std::reverse(str.begin(), str.end());
  return str;
}

} // namespace reverse_string
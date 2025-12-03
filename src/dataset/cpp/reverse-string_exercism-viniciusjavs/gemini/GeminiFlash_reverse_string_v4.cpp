#include "reverse_string.h"
#include <algorithm>
#include <string>

namespace reverse_string {

std::string reverse_string(std::string str) {
  if (str.empty()) {
    return str;
  }
  std::reverse(str.begin(), str.end());
  return str;
}

} // namespace reverse_string
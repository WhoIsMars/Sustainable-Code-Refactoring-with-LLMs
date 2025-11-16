#include "reverse_string.h"

namespace reverse_string {

string reverse_string(string str) {
  for (size_t i = 0, j = str.size() - 1; i < j; ++i, --j) {
    std::swap(str[i], str[j]);
  }
  return str;
}

} // namespace reverse_string
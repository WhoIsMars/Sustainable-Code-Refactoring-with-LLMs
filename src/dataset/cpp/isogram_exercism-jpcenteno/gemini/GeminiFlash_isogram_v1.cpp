#include "isogram.h"

#include <algorithm>
#include <cctype>

namespace isogram {

bool is_isogram(const std::string& str) {
  std::array<bool, 26> seen = {false};

  for (char c : str) {
    if (std::isalpha(c)) {
      char lower_c = std::tolower(c);
      size_t index = lower_c - 'a';
      if (seen[index]) {
        return false;
      }
      seen[index] = true;
    }
  }

  return true;
}

} // namespace isogram
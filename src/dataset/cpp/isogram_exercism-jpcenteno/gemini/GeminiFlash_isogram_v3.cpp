#include "isogram.h"

#include <algorithm>
#include <cctype>

namespace isogram {

bool is_isogram(const std::string& str) {
  std::size_t char_counts[26] = {0};

  for (char c : str) {
    if (std::isalpha(c)) {
      char lower_c = std::tolower(c);
      std::size_t index = lower_c - 'a';
      if (char_counts[index] > 0) {
        return false;
      }
      char_counts[index]++;
    }
  }

  return true;
}

}  // namespace isogram
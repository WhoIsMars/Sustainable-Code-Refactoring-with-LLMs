#include "isogram.h"
#include <cctype>
#include <string>
#include <unordered_set>

namespace isogram {

bool is_isogram(const std::string& word) {
  std::unordered_set<char> seen_chars;
  for (char c : word) {
    if (std::isalpha(c)) {
      char lower_c = std::tolower(c);
      if (seen_chars.count(lower_c) > 0) {
        return false;
      }
      seen_chars.insert(lower_c);
    }
  }
  return true;
}

}  // namespace isogram
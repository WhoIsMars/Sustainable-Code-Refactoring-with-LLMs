#include "isogram.h"
#include <cctype>
#include <string>
#include <unordered_set>

namespace isogram {

bool is_isogram(std::string word) {
  std::unordered_set<char> seen;
  for (char c : word) {
    if (std::isalpha(c)) {
      char lower_c = std::tolower(c);
      if (seen.count(lower_c) > 0) {
        return false;
      }
      seen.insert(lower_c);
    }
  }
  return true;
}

} // namespace isogram
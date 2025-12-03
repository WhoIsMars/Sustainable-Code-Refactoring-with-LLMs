#include <algorithm>
#include <cctype>
#include <string>

#include "isogram.h"

namespace isogram {

bool is_isogram(const std::string& phrase) {
  std::string processed_phrase;
  processed_phrase.reserve(phrase.length());

  for (char ch : phrase) {
    if (std::isalpha(ch)) {
      processed_phrase += std::tolower(ch);
    }
  }

  std::sort(processed_phrase.begin(), processed_phrase.end());

  for (size_t i = 1; i < processed_phrase.length(); ++i) {
    if (processed_phrase[i] == processed_phrase[i - 1]) {
      return false;
    }
  }

  return true;
}

}  // namespace isogram
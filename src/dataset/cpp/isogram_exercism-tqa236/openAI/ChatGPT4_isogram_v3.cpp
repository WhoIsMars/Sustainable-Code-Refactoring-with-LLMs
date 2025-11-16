#include "isogram.h"
#include <bitset>
#include <cctype>

bool isogram::is_isogram(const std::string& phrase) {
  std::bitset<26> letters;
  for (char c : phrase) {
    if (std::isalpha(c)) {
      int position = std::tolower(c) - 'a';
      if (letters.test(position)) {
        return false;
      }
      letters.set(position);
    }
  }
  return true;
}
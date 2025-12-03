#include "isogram.h"
#include <cctype>

bool isogram::is_isogram(const std::string& phrase) {
  if (phrase.empty()) return true;

  unsigned int seen = 0;
  for (unsigned char c : phrase) {
    unsigned char lower_c = std::tolower(c);
    if (lower_c >= 'a' && lower_c <= 'z') {
      unsigned int bit = 1 << (lower_c - 'a');
      if (seen & bit) {
        return false;
      }
      seen |= bit;
    }
  }
  return true;
}
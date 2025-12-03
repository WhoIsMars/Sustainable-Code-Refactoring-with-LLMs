#include "isogram.h"
#include <cctype>

bool isogram::is_isogram(const std::string& phrase) {
  unsigned int letters = 0;
  for (unsigned char c : phrase) {
    unsigned char lower_c = std::tolower(c);
    if (lower_c >= 'a' && lower_c <= 'z') {
      int position = lower_c - 'a';
      unsigned int mask = 1 << position;
      if (letters & mask) {
        return false;
      }
      letters |= mask;
    }
  }
  return true;
}
#include "isogram.h"
#include <bitset>

bool isogram::is_isogram(const std::string& phrase) {
  std::bitset<26> letters;
  for (unsigned char c : phrase) {
    int position = std::tolower(c) - 'a';
    if ((position >= 0) && (position <= 25)) {
      if (letters[position]) {
        return false;
      }
      letters.set(position);
    }
  }
  return true;
}

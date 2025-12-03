#include "scrabble_score.h"
#include <cctype>

int scrabble_score::score(std::string s) {
  static const int scores[26] = {
      1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

  int sum = 0;
  for (char ch : s) {
    char upper_ch = std::toupper(ch);
    if (upper_ch >= 'A' && upper_ch <= 'Z') {
      sum += scores[upper_ch - 'A'];
    }
  }
  return sum;
}
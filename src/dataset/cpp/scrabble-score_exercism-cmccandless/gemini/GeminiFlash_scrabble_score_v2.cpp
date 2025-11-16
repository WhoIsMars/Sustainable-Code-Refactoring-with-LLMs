#include "scrabble_score.h"
#include <cctype>

int scrabble_score::score(const std::string& s) {
  static const int scores[26] = {
      1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

  int sum = 0;
  for (unsigned char ch : s) {
    if (std::isalpha(ch)) {
      sum += scores[std::toupper(ch) - 'A'];
    }
  }
  return sum;
}
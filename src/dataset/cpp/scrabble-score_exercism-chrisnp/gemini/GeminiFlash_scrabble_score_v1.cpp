#include "scrabble_score.h"
#include <algorithm>

int scrabble_score::score(const std::string& word) {
  int score = 0;
  std::string upper_word = word;
  std::transform(upper_word.begin(), upper_word.end(), upper_word.begin(), ::toupper);

  for (char c : upper_word) {
    score += LETTER_SCORES[c - 'A'];
  }
  return score;
}
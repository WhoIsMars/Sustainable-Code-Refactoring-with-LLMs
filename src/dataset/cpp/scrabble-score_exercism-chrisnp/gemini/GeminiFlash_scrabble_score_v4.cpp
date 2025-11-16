#include "scrabble_score.h"
#include <algorithm>
#include <cctype>

int scrabble_score::score(const std::string& word) {
  int score = 0;
  for (char c : word) {
    score += LETTER_SCORES[std::toupper(static_cast<unsigned char>(c)) - 'A'];
  }
  return score;
}
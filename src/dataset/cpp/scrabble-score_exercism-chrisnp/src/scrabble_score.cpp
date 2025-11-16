#include "scrabble_score.h"

int scrabble_score::score(const std::string& word) {
  int score {0};
  for (auto c : word) {
    score += LETTER_SCORES[toupper(c) - 'A'];
  }
  return score;
}

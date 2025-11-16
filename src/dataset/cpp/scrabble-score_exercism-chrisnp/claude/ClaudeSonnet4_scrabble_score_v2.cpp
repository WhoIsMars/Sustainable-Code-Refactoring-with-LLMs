#include "scrabble_score.h"

int scrabble_score::score(const std::string& word) {
  int score = 0;
  for (const char c : word) {
    score += LETTER_SCORES[c - 'A'];
  }
  return score;
}
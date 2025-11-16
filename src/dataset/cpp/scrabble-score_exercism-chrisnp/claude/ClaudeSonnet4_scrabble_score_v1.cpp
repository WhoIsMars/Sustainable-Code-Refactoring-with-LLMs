#include "scrabble_score.h"

int scrabble_score::score(const std::string& word) {
  int score = 0;
  for (const char c : word) {
    if (c >= 'A' && c <= 'Z') {
      score += LETTER_SCORES[c - 'A'];
    } else if (c >= 'a' && c <= 'z') {
      score += LETTER_SCORES[c - 'a'];
    }
  }
  return score;
}
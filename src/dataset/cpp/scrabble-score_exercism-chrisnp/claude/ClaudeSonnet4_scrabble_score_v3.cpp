#include "scrabble_score.h"

int scrabble_score::score(const std::string& word) {
  int total_score = 0;
  const char* str = word.c_str();
  const char* end = str + word.size();
  
  while (str < end) {
    char c = *str++;
    if (c >= 'A' && c <= 'Z') {
      total_score += LETTER_SCORES[c - 'A'];
    } else if (c >= 'a' && c <= 'z') {
      total_score += LETTER_SCORES[c - 'a'];
    }
  }
  
  return total_score;
}
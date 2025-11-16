#include "scrabble_score.h"

#include <array>
#include <cctype>
#include <string>

namespace scrabble_score {
const std::array<int, 26> letter_values = {
    1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int score(std::string const& word) {
  int total_score = 0;
  for (unsigned char c : word) {
    if (std::isalpha(c)) {
      total_score += letter_values[std::toupper(c) - 'A'];
    }
  }
  return total_score;
}
}  // namespace scrabble_score
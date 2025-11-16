#include "scrabble_score.h"

namespace scrabble_score {
static constexpr int letter_values[26] = {
    1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3,
    1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10
};

int score(std::string const& word) {
  int total = 0;
  for (unsigned char c : word) {
    if (c >= 'A' && c <= 'Z') {
      total += letter_values[c - 'A'];
    } else if (c >= 'a' && c <= 'z') {
      total += letter_values[c - 'a'];
    }
  }
  return total;
}
}  // namespace scrabble_score
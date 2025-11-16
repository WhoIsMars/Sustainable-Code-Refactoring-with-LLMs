#include "scrabble_score.h"

namespace scrabble_score {
static constexpr int letter_values[26] = {
    1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3,
    1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10
};

int score(std::string const& word) {
  int total = 0;
  for (char c : word) {
    unsigned char upper = c & ~32;
    if (upper >= 'A' && upper <= 'Z') {
      total += letter_values[upper - 'A'];
    }
  }
  return total;
}
}  // namespace scrabble_score
#include "scrabble_score.h"

#include <algorithm>
#include <numeric>
#include <string>
#include <unordered_map>

namespace scrabble_score {

int score(std::string const& word) {
  static constexpr std::array<int, 26> letter_values = {
      1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8,
      4, 10};

  int total_score = 0;
  for (unsigned char c : word) {
    unsigned char upper_c = std::toupper(c);
    if (upper_c >= 'A' && upper_c <= 'Z') {
      total_score += letter_values[upper_c - 'A'];
    }
  }
  return total_score;
}
}  // namespace scrabble_score
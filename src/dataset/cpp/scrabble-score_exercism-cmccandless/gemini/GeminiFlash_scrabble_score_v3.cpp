#include "scrabble_score.h"
#include <cctype>
#include <unordered_map>

int scrabble_score::score(std::string s) {
  static const std::unordered_map<char, int> scores = {
      {'A', 1},  {'E', 1},  {'I', 1},  {'O', 1},  {'U', 1},  {'L', 1},
      {'N', 1},  {'R', 1},  {'S', 1},  {'T', 1},  {'D', 2},  {'G', 2},
      {'B', 3},  {'C', 3},  {'M', 3},  {'P', 3},  {'F', 4},  {'H', 4},
      {'V', 4},  {'W', 4},  {'Y', 4},  {'K', 5},  {'J', 8},  {'X', 8},
      {'Q', 10}, {'Z', 10}};

  int sum = 0;
  for (char ch : s) {
    char upper_ch = std::toupper(ch);
    auto it = scores.find(upper_ch);
    if (it != scores.end()) {
      sum += it->second;
    }
  }
  return sum;
}
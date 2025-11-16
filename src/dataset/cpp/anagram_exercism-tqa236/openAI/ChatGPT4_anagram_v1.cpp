#include "anagram.h"
#include <algorithm>
#include <unordered_map>

namespace anagram {
anagram::anagram(std::string const& word) {
  lower_word = word;
  std::transform(lower_word.begin(), lower_word.end(), lower_word.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  normalized_word = lower_word;
  std::sort(normalized_word.begin(), normalized_word.end());
}

std::tuple<std::string, std::string> anagram::process_word(std::string const& word) {
  std::string lower_word = word;
  std::transform(lower_word.begin(), lower_word.end(), lower_word.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  std::string normalized_word = lower_word;
  std::sort(normalized_word.begin(), normalized_word.end());
  return {std::move(lower_word), std::move(normalized_word)};
}

std::vector<std::string> anagram::matches(
    std::vector<std::string> const& candidates) {
  std::vector<std::string> anagrams;
  for (auto const& candidate : candidates) {
    if (candidate.size() != lower_word.size()) continue;
    bool is_anagram = true;
    std::unordered_map<char, int> char_count;

    for (char c : candidate) {
      char_count[std::tolower(c)]++;
    }
    for (char c : lower_word) {
      if (--char_count[c] < 0) {
        is_anagram = false;
        break;
      }
    }
    if (is_anagram && candidate != lower_word) {
      anagrams.push_back(candidate);
    }
  }
  return anagrams;
}
}  // namespace anagram
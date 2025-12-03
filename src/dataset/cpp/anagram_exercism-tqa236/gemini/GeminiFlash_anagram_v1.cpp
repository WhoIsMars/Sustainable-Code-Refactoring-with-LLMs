#include "anagram.h"
#include <algorithm>
#include <cctype>
#include <tuple>
#include <vector>

namespace anagram {

anagram::anagram(const std::string& word) {
  lower_word = to_lower(word);
  normalized_word = lower_word;
  std::sort(normalized_word.begin(), normalized_word.end());
}

std::string anagram::to_lower(const std::string& word) {
  std::string lower_word = word;
  std::transform(lower_word.begin(), lower_word.end(), lower_word.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  return lower_word;
}

std::vector<std::string> anagram::matches(
    const std::vector<std::string>& candidates) {
  std::vector<std::string> anagrams;
  for (const auto& candidate : candidates) {
    std::string lower_candidate = to_lower(candidate);
    if (lower_candidate == lower_word) continue;

    std::string normalized_candidate = lower_candidate;
    std::sort(normalized_candidate.begin(), normalized_candidate.end());

    if (normalized_candidate == normalized_word) {
      anagrams.push_back(candidate);
    }
  }
  return anagrams;
}

}  // namespace anagram
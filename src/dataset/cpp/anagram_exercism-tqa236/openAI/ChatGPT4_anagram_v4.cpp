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

std::vector<std::string> anagram::matches(
    std::vector<std::string> const& candidates) {
  std::vector<std::string> anagrams;
  for (const auto& candidate : candidates) {
    if (candidate.size() != lower_word.size()) continue;

    std::string lower_candidate = candidate;
    std::transform(lower_candidate.begin(), lower_candidate.end(), lower_candidate.begin(),
                   [](unsigned char c) { return std::tolower(c); });

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
#include "anagram.h"
#include <algorithm>
#include <unordered_map>

namespace anagram {

anagram::anagram(std::string const& word) {
  lower_word = to_lower(word);
  normalized_word = normalize(lower_word);
}

std::string anagram::to_lower(const std::string& word) {
  std::string result = word;
  std::transform(result.begin(), result.end(), result.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  return result;
}

std::string anagram::normalize(const std::string& word) {
  std::string result = word;
  std::sort(result.begin(), result.end());
  return result;
}

std::vector<std::string> anagram::matches(
    std::vector<std::string> const& candidates) {
  std::vector<std::string> anagrams;
  for (const auto& candidate : candidates) {
    if (candidate.size() != lower_word.size()) continue; // Early exit for non-matching lengths
    std::string lower_candidate = to_lower(candidate);
    if (lower_candidate == lower_word) continue; // Skip identical words
    if (normalize(lower_candidate) == normalized_word) {
      anagrams.push_back(candidate);
    }
  }
  return anagrams;
}

}  // namespace anagram
#include "anagram.h"
#include <algorithm>
#include <unordered_map>

namespace anagram {

anagram::anagram(std::string const& word) {
  std::tie(lower_word, normalized_word) = process_word(word);
}

std::tuple<std::string, std::string> anagram::process_word(std::string word) {
  std::transform(word.begin(), word.end(), word.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  std::string normalized_word = word;
  std::sort(normalized_word.begin(), normalized_word.end());
  return {std::move(word), std::move(normalized_word)};
}

std::vector<std::string> anagram::matches(
    std::vector<std::string> const& candidates) {
  std::vector<std::string> anagrams;
  for (auto const& candidate : candidates) {
    if (candidate.size() != lower_word.size()) continue;
    auto [lower_candidate, normalized_candidate] = process_word(candidate);
    if (normalized_candidate == normalized_word && lower_candidate != lower_word) {
      anagrams.push_back(candidate);
    }
  }
  return anagrams;
}

}  // namespace anagram
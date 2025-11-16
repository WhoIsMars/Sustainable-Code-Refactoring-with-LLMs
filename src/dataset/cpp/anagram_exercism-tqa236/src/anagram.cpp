#include "anagram.h"
#include <algorithm>

namespace anagram {
anagram::anagram(std::string const& word) {
  std::tuple<std::string, std::string> processed_words = process_word(word);
  std::tie(lower_word, normalized_word) = processed_words;
}

std::tuple<std::string, std::string> anagram::process_word(std::string word) {
  auto lower_word = std::move(word);
  std::transform(lower_word.begin(), lower_word.end(), lower_word.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  auto normalized_word = lower_word;
  sort(normalized_word.begin(), normalized_word.end());
  return make_tuple(std::move(lower_word), std::move(normalized_word));
}
std::vector<std::string> anagram::matches(
    std::vector<std::string> const& candidates) {
  std::vector<std::string> anagrams;
  for (auto& candidate : candidates) {
    auto processed_candidates = process_word(candidate);
    std::string lower_candidate, normalized_candidate;
    std::tie(lower_candidate, normalized_candidate) = processed_candidates;
    if ((normalized_candidate == normalized_word) &&
        (lower_candidate != lower_word)) {
      anagrams.push_back(candidate);
    }
  }
  return anagrams;
}
}  // namespace anagram

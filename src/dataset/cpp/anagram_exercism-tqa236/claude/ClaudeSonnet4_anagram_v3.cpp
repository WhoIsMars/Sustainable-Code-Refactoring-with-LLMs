#include "anagram.h"
#include <algorithm>
#include <cctype>

namespace anagram {
anagram::anagram(std::string const& word) {
  lower_word.reserve(word.size());
  normalized_word.reserve(word.size());
  
  for (char c : word) {
    char lower_c = std::tolower(static_cast<unsigned char>(c));
    lower_word += lower_c;
    normalized_word += lower_c;
  }
  
  std::sort(normalized_word.begin(), normalized_word.end());
}

std::tuple<std::string, std::string> anagram::process_word(std::string word) {
  std::string lower_word;
  lower_word.reserve(word.size());
  
  for (char c : word) {
    lower_word += std::tolower(static_cast<unsigned char>(c));
  }
  
  std::string normalized_word = lower_word;
  std::sort(normalized_word.begin(), normalized_word.end());
  
  return std::make_tuple(std::move(lower_word), std::move(normalized_word));
}

std::vector<std::string> anagram::matches(
    std::vector<std::string> const& candidates) {
  std::vector<std::string> anagrams;
  anagrams.reserve(candidates.size());
  
  for (const auto& candidate : candidates) {
    if (candidate.size() != lower_word.size()) {
      continue;
    }
    
    std::string normalized_candidate;
    normalized_candidate.reserve(candidate.size());
    
    bool is_same_word = true;
    for (size_t i = 0; i < candidate.size(); ++i) {
      char lower_c = std::tolower(static_cast<unsigned char>(candidate[i]));
      normalized_candidate += lower_c;
      if (is_same_word && lower_c != lower_word[i]) {
        is_same_word = false;
      }
    }
    
    if (!is_same_word) {
      std::sort(normalized_candidate.begin(), normalized_candidate.end());
      if (normalized_candidate == normalized_word) {
        anagrams.push_back(candidate);
      }
    }
  }
  
  return anagrams;
}
}  // namespace anagram
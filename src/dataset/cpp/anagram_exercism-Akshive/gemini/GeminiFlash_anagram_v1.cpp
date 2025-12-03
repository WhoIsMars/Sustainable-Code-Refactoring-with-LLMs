#include "anagram.h"
#include <algorithm>
#include <cctype>
#include <string>
#include <vector>
#include <unordered_set>

namespace anagram {

anagram::anagram(std::string word) : original_word(word) {
  std::string temp = word;
  std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
  std::sort(temp.begin(), temp.end());
  sorted_lowercase = temp;
}

std::vector<std::string> anagram::matches(std::list<std::string> words) {
  std::vector<std::string> result;
  std::string original_word_lower = original_word;
  std::transform(original_word_lower.begin(), original_word_lower.end(), original_word_lower.begin(), ::tolower);


  for (const auto& word_to_match : words) {
    std::string word_to_match_lower = word_to_match;
    std::transform(word_to_match_lower.begin(), word_to_match_lower.end(), word_to_match_lower.begin(), ::tolower);

    if (original_word_lower == word_to_match_lower) continue;

    std::string sorted_word = word_to_match_lower;
    std::sort(sorted_word.begin(), sorted_word.end());

    if (sorted_word == sorted_lowercase) {
      result.push_back(word_to_match);
    }
  }
  return result;
}

}  // namespace anagram
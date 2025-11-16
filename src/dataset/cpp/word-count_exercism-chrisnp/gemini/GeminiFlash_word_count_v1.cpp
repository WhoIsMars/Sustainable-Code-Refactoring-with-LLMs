#include "word_count.h"
#include <algorithm>
#include <cctype>
#include <string>
#include <unordered_map>

using std::string;
using word_count::words_map_t;

const words_map_t word_count::words(const string &text) {
  words_map_t wordcount;
  string word;
  word.reserve(16); // Pre-allocate some space to reduce reallocations

  for (size_t i = 0; i < text.length(); ++i) {
    char c = text[i];
    if (std::isalnum(c)) {
      word += static_cast<char>(std::tolower(c));
    } else if (c == '\'' && i + 1 < text.length() && std::isalnum(text[i + 1])) {
      word += c;
    } else if (!word.empty() && (c == ' ' || c == ',' || c == '\n')) {
      ++wordcount[word];
      word.clear();
      word.reserve(16); // Reset the reserved space after clearing
    }
  }

  if (!word.empty()) {
    ++wordcount[word];
  }

  return wordcount;
}
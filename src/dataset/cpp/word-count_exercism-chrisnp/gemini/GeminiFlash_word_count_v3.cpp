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
  word.reserve(16); 

  auto process_word = [&]() {
    if (!word.empty()) {
      ++wordcount[word];
      word.clear();
      word.reserve(16);
    }
  };

  for (size_t i = 0; i < text.length(); ++i) {
    char c = text[i];
    if (isalnum(c)) {
      word += static_cast<char>(std::tolower(c));
    } else if (c == '\'' && i + 1 < text.length() && isalnum(text[i + 1])) {
      word += c;
    } else if (c == ' ' || c == ',' || c == '\n') {
      process_word();
    }
  }

  process_word(); 
  return wordcount;
}
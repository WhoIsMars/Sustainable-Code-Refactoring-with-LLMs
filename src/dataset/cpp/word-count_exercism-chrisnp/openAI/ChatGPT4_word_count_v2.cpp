#include "word_count.h"
#include <unordered_map>
#include <cctype>
#include <sstream>

using std::string;
using word_count::words_map_t;

const words_map_t word_count::words(const string &text) {
    constexpr auto is_word_char = [](char c) noexcept -> bool {
        return std::isalnum(c) || c == '\'';
    };

    words_map_t wordcount;
    std::string word;
    for (char c : text) {
        if (std::isalnum(c)) {
            word += std::tolower(c);
        } else if (c == '\'' && !word.empty() && std::isalnum(word.back())) {
            word += c;
        } else if (!word.empty()) {
            ++wordcount[word];
            word.clear();
        }
    }
    if (!word.empty()) {
        ++wordcount[word];
    }
    return wordcount;
}
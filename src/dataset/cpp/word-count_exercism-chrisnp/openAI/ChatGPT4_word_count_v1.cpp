#include "word_count.h"
#include <unordered_map>
#include <cctype>

using std::string;
using word_count::words_map_t;

const words_map_t word_count::words(const string &text) {
    constexpr auto is_word_delimiter = [](char c) noexcept -> bool {
        return c == ' ' || c == ',' || c == '\n';
    };

    words_map_t wordcount;
    string word;
    word.reserve(32); // Reserve space to minimize reallocations

    for (size_t i = 0; i < text.size(); ++i) {
        char c = std::tolower(text[i]);
        if (std::isalnum(c)) {
            word += c;
        } else if (c == '\'' && i + 1 < text.size() && std::isalnum(text[i + 1])) {
            word += c;
        } else if (!word.empty() && is_word_delimiter(c)) {
            ++wordcount[word];
            word.clear();
        }
    }

    if (!word.empty()) {
        ++wordcount[word];
    }

    return wordcount;
}
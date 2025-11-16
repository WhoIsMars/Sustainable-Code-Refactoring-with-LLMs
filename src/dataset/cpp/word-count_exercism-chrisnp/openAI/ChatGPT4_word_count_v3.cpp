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
    word.reserve(32); // Reserve a reasonable initial size for the word buffer

    for (size_t i = 0, len = text.size(); i <= len; ++i) {
        char c = (i < len) ? text[i] : '\0'; // Add a null character at the end to flush the last word
        if (std::isalnum(c)) {
            word += std::tolower(c);
        } else if (c == '\'' && i + 1 < len && std::isalnum(text[i + 1])) {
            word += c;
        } else if (!word.empty() && (is_word_delimiter(c) || c == '\0')) {
            ++wordcount[word];
            word.clear();
        }
    }

    return wordcount;
}
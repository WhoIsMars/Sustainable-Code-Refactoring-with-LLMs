#include "word_count.h"
#include <vector>

using std::string;
using word_count::words_map_t;

const words_map_t word_count::words( const string &text ) {
    constexpr auto word_delimiter = [&](const char c) noexcept -> bool {
        return c == ' ' || c == ',' || c == '\n';
    };
    words_map_t wordcount {};
    std::vector<char> wordchars {};
    for ( unsigned int i = 0; i < text.length(); i++ ) {
        const auto &c = static_cast<char>(text[i]);
        if ( isalnum(c) ) wordchars.push_back(std::tolower(c));
        if ( !wordchars.empty() ) { 
            if ( c == '\'' && isalnum(text[i + 1]) ) wordchars.push_back(c);
            if ( word_delimiter(c) ) {
                ++wordcount[string(wordchars.begin(), wordchars.end())];
                wordchars.clear();
            }
        }
    }
    wordcount[string(wordchars.begin(), wordchars.end())] += 1;
    return wordcount;
}

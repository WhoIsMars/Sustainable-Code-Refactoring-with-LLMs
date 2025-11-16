#include "word_count.h"
#include <string>
#include <cctype>

using std::string;
using word_count::words_map_t;

const words_map_t word_count::words( const string &text ) {
    words_map_t wordcount;
    wordcount.reserve(text.length() / 6);
    
    string current_word;
    current_word.reserve(32);
    
    const char* data = text.data();
    const size_t length = text.length();
    
    for (size_t i = 0; i < length; ++i) {
        const char c = data[i];
        
        if (std::isalnum(static_cast<unsigned char>(c))) {
            current_word += std::tolower(static_cast<unsigned char>(c));
        } else if (c == '\'' && i + 1 < length && 
                   std::isalnum(static_cast<unsigned char>(data[i + 1])) && 
                   !current_word.empty()) {
            current_word += c;
        } else if (!current_word.empty() && (c == ' ' || c == ',' || c == '\n')) {
            ++wordcount[current_word];
            current_word.clear();
        }
    }
    
    if (!current_word.empty()) {
        ++wordcount[current_word];
    }
    
    return wordcount;
}
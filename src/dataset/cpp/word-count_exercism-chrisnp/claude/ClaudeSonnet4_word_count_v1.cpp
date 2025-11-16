#include "word_count.h"
#include <string>

using std::string;
using word_count::words_map_t;

const words_map_t word_count::words( const string &text ) {
    words_map_t wordcount {};
    string current_word {};
    current_word.reserve(32); // Reserve space for typical word length
    
    const char* data = text.data();
    const size_t length = text.length();
    
    for ( size_t i = 0; i < length; i++ ) {
        const char c = data[i];
        
        if ( isalnum(c) ) {
            current_word += static_cast<char>(std::tolower(c));
        } else if ( c == '\'' && i + 1 < length && isalnum(data[i + 1]) && !current_word.empty() ) {
            current_word += c;
        } else if ( !current_word.empty() && (c == ' ' || c == ',' || c == '\n') ) {
            ++wordcount[current_word];
            current_word.clear();
        }
    }
    
    if ( !current_word.empty() ) {
        ++wordcount[current_word];
    }
    
    return wordcount;
}
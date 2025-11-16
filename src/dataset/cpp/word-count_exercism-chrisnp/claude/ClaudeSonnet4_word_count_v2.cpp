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
        
        if ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') ) {
            current_word += (c >= 'A' && c <= 'Z') ? c + 32 : c; // Fast lowercase conversion
        } else if ( c == '\'' && i + 1 < length && 
                   (((data[i+1] >= 'a' && data[i+1] <= 'z') || (data[i+1] >= 'A' && data[i+1] <= 'Z') || (data[i+1] >= '0' && data[i+1] <= '9')) && !current_word.empty()) ) {
            current_word += c;
        } else if ( !current_word.empty() ) {
            ++wordcount[current_word];
            current_word.clear();
        }
    }
    
    if ( !current_word.empty() ) {
        ++wordcount[current_word];
    }
    
    return wordcount;
}
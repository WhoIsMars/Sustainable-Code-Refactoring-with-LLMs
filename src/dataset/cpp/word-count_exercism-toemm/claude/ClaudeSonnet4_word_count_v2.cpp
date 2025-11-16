#include "word_count.h"

#include <unordered_map>
#include <string>
#include <cctype>

namespace word_count {

using namespace std;

inline bool is_letter(char ch) {
    return isalnum(ch);
}

unordered_map<string, int> words(const string& sentence) {
    unordered_map<string, int> word_count;
    string word;
    word.reserve(32); // Reserve space for typical word length
    
    const size_t len = sentence.length();
    
    for (size_t i = 0; i < len; ++i) {
        char ch = sentence[i];
        char ch_peak = (i + 1 < len) ? sentence[i + 1] : '\0';
        
        bool is_apostrophe = (ch == '\'');
        
        if (is_letter(ch) || (is_apostrophe && !word.empty() && is_letter(ch_peak))) {
            word += static_cast<char>(tolower(ch));
        } else if (!word.empty()) {
            ++word_count[word];
            word.clear();
        }
    }
    
    if (!word.empty()) {
        ++word_count[word];
    }
    
    return word_count;
}

}  // namespace word_count
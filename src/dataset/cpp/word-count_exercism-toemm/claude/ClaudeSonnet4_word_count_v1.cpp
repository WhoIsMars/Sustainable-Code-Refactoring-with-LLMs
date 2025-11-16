#include "word_count.h"

#include <unordered_map>
#include <string>
#include <cctype>

namespace word_count {

using namespace std;

inline bool is_letter(char ch) {
    return isalnum(ch);
}

unordered_map<string, int> words(string sentence) {
    unordered_map<string, int> word_count;
    word_count.reserve(sentence.length() / 5); // rough estimate for average word length
    
    string word;
    word.reserve(20); // reserve space for typical word length
    
    const char* data = sentence.data();
    const size_t len = sentence.length();
    
    for (size_t i = 0; i < len; ++i) {
        char ch = data[i];
        char ch_next = (i + 1 < len) ? data[i + 1] : '\0';
        
        bool is_apostrophe = (ch == '\'');
        
        if (is_letter(ch) || (is_apostrophe && !word.empty() && is_letter(ch_next))) {
            word += static_cast<char>(tolower(static_cast<unsigned char>(ch)));
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
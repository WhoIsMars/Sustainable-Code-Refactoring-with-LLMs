#include "word_count.h"

#include <unordered_map>
#include <string>
#include <cctype>

namespace word_count {

using namespace std;

bool is_letter(char ch) {
    return isalnum(ch);
}

unordered_map<string, int> words(string sentence) {
    unordered_map<string, int> word_count;
    word_count.reserve(sentence.length() / 5);
    
    string word;
    word.reserve(32);
    
    const char* data = sentence.data();
    const size_t len = sentence.length();
    
    for (size_t i = 0; i < len; ++i) {
        const char ch = data[i];
        const char next_ch = (i + 1 < len) ? data[i + 1] : '\0';
        
        const bool is_apostrophe = (ch == '\'');
        
        if (is_letter(ch) || (is_apostrophe && !word.empty() && is_letter(next_ch))) {
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
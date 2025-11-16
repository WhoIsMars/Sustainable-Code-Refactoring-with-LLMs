#include "word_count.h"

#include <unordered_map>
#include <string>
#include <cctype>

namespace word_count {

using namespace std;

bool is_letter(char ch) {
    return isalnum(ch);
}

map<string, int> words(string sentence) {
    unordered_map<string, int> word_count;
    string word;
    word.reserve(32);
    
    const size_t len = sentence.length();
    
    for (size_t i = 0; i < len; ++i) {
        const char ch = sentence[i];
        const char ch_peak = (i + 1 < len) ? sentence[i + 1] : '\0';
        
        const bool is_apostrophe = (ch == '\'');
        
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
    
    return map<string, int>(word_count.begin(), word_count.end());
}

}  // namespace word_count
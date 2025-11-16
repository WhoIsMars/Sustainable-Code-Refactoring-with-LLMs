#include "word_count.h"

#include <unordered_map>
#include <string>
#include <cctype>

namespace word_count {

using namespace std;

bool is_letter(char ch) {
    return isalnum(ch);
}

unordered_map<string, int> words(const string& sentence) {
    unordered_map<string, int> word_count;
    string word;

    for (size_t i = 0; i < sentence.size(); ++i) {
        char ch = tolower(sentence[i]);
        bool is_apostrophe = (ch == '\'');
        bool is_valid_apostrophe = is_apostrophe && !word.empty() && i + 1 < sentence.size() && is_letter(sentence[i + 1]);

        if (is_letter(ch) || is_valid_apostrophe) {
            word += ch;
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
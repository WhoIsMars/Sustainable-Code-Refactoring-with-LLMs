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

        if (is_letter(ch)) {
            word += ch;
        } else if (ch == '\'' && !word.empty() && i + 1 < sentence.size() && is_letter(sentence[i + 1])) {
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
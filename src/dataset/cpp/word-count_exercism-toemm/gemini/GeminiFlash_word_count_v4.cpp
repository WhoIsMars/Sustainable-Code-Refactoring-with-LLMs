#include "word_count.h"

#include <map>
#include <string>
#include <cctype>
#include <algorithm>

namespace word_count {

using namespace std;

map<string, int> words(string sentence) {
    map<string, int> word_count;
    string word;
    word.reserve(sentence.length()); // Pre-allocate memory

    for (size_t i = 0; i < sentence.length(); ++i) {
        char ch = sentence[i];

        if (isalnum(ch) || (ch == '\'' && !word.empty() && i + 1 < sentence.length() && isalnum(sentence[i + 1]))) {
            word += tolower(ch);
        } else if (!word.empty()) {
            word_count[word]++;
            word.clear();
            word.reserve(sentence.length()); //Re-reserve after clear
        }
    }

    if (!word.empty()) {
        word_count[word]++;
    }

    return word_count;
}

}  // namespace word_count
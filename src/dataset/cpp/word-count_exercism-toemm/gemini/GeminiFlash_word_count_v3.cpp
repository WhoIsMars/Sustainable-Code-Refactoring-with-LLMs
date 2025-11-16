#include "word_count.h"

#include <map>
#include <string>
#include <algorithm>
#include <cctype>

namespace word_count {

using namespace std;

map<string, int> words(string sentence) {
    map<string, int> word_count;
    string word;
    word.reserve(20); // Pre-allocate some space to reduce reallocations

    for (size_t i = 0; i < sentence.length(); ++i) {
        char ch = sentence[i];

        if (isalnum(ch)) {
            word += tolower(ch);
        } else if (ch == '\'' && !word.empty() && i + 1 < sentence.length() && isalnum(sentence[i + 1])) {
            word += ch;
        } else if (!word.empty()) {
            word_count[word]++;
            word.clear();
        }
    }

    if (!word.empty()) {
        word_count[word]++;
    }

    return word_count;
}

}  // namespace word_count
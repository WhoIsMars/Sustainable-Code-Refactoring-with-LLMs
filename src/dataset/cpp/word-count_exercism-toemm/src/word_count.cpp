#include "word_count.h"

#include <map>
#include <vector>
#include <array>

namespace word_count {

using namespace std;

bool is_letter(char ch) {
    return isalpha(ch) || isdigit(ch);
}

map<string, int> words(string sentence) {

    map<string, int> word_count;
    string word;

    for (auto it = sentence.begin(); it != sentence.end(); it++) {

        auto ch = *it;
        char ch_peak = *next(it); // out of loop so ch_peak is '\0'

        bool is_apostrophe = (ch == '\'');

        if (is_letter(ch) || (is_apostrophe && !word.empty() && is_letter(ch_peak))) {
            word += tolower(ch);
            if (ch_peak == '\0') ++word_count[word]; // flush last word before end of string

        } else if (!is_letter(ch) && !word.empty()) {
            word_count[word]++;
            word.clear();
        }
    }

    return word_count;

}



}  // namespace word_count

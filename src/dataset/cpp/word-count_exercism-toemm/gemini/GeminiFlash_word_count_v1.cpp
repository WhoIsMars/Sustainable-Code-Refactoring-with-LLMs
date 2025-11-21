#include "word_count.h"

#include <algorithm>
#include <cctype>
#include <map>
#include <string>
#include <sstream>

namespace word_count {

using namespace std;

map<string, int> words(string sentence) {
    map<string, int> word_count;
    stringstream ss(sentence);
    string word;

    while (ss >> word) {
        // Remove leading and trailing non-alphanumeric characters
        word.erase(remove_if(word.begin(), word.end(), [](char c) {
                        return !isalnum(c) && c != '\'';
                    }),
                    word.end());
        word.erase(0, word.find_first_not_of("\'"));

        // Convert to lowercase
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        // Remove leading and trailing apostrophes if they exist alone
        if (word.length() > 2 && word.front() == '\'' && word.back() == '\'') {
            word = word.substr(1, word.length() - 2);
        } else if (word.length() > 0 && (word.front() == '\'' || word.back() == '\'')) {
            if (word.length() == 1 && word[0] == '\'') {
                word = "";
            } else if (word.front() == '\'') {
                word = word.substr(1);
            } else if (word.back() == '\'') {
                word.pop_back();
            }
        }

        if (!word.empty()) {
            word_count[word]++;
        }
    }

    return word_count;
}

}  // namespace word_count
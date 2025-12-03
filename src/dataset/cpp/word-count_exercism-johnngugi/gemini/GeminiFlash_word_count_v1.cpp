#include <string>
#include <map>
#include <iostream>
#include "word_count.h"
#include <algorithm>
#include <cctype>

using namespace std;

map<string, int> word_count::words(string sen) {
    map<string, int> word_counts;
    string current_word;
    sen += ' '; // Add a space to simplify the loop

    for (char c : sen) {
        if (isalnum(c)) {
            current_word += tolower(c);
        } else if (c == '\'' && !current_word.empty()) {
            current_word += c;
        } else if (!current_word.empty()) {
            if (current_word.back() == '\'') {
                current_word.pop_back();
            }

            auto it = word_counts.find(current_word);
            if (it != word_counts.end()) {
                it->second++;
            } else {
                word_counts[current_word] = 1;
            }
            current_word.clear();
        }
    }

    return word_counts;
}
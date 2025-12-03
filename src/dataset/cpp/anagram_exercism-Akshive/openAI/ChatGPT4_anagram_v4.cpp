#include "anagram.h"
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <string>
#include <list>

using namespace std;

namespace anagram {

    anagram::anagram(string word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        sort(word.begin(), word.end());
        this->key = word;
    }

    vector<string> anagram::matches(list<string> words) {
        vector<string> ans;
        for (const auto& word_to_match : words) {
            string lower_word = word_to_match;
            transform(lower_word.begin(), lower_word.end(), lower_word.begin(), ::tolower);
            if (lower_word == this->key) continue;
            string sorted_word = lower_word;
            sort(sorted_word.begin(), sorted_word.end());
            if (sorted_word == this->key) {
                ans.push_back(word_to_match);
            }
        }
        return ans;
    }

}
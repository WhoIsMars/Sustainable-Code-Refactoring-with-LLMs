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
        this->word = word;
        this->sorted_word = word;
        sort(this->sorted_word.begin(), this->sorted_word.end());
    }

    vector<string> anagram::matches(list<string> words) {
        vector<string> ans;
        for (const auto& candidate : words) {
            string lower_candidate = candidate;
            transform(lower_candidate.begin(), lower_candidate.end(), lower_candidate.begin(), ::tolower);
            if (lower_candidate == word) continue;

            string sorted_candidate = lower_candidate;
            sort(sorted_candidate.begin(), sorted_candidate.end());
            if (sorted_candidate == sorted_word) {
                ans.push_back(candidate);
            }
        }
        return ans;
    }

}
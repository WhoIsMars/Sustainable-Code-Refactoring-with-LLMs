#include "anagram.h"
#include <algorithm>
#include <cctype>
#include <unordered_map>
#include <vector>
#include <list>
#include <string>

using namespace std;

namespace anagram {

    anagram::anagram(string word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        sort(word.begin(), word.end());
        this->word = word;
    }

    vector<string> anagram::matches(list<string> words) {
        vector<string> ans;
        for (const auto& candidate : words) {
            string lower_candidate = candidate;
            transform(lower_candidate.begin(), lower_candidate.end(), lower_candidate.begin(), ::tolower);
            if (lower_candidate == word) continue;

            string sorted_candidate = lower_candidate;
            sort(sorted_candidate.begin(), sorted_candidate.end());
            if (sorted_candidate == word) {
                ans.push_back(candidate);
            }
        }
        return ans;
    }

}
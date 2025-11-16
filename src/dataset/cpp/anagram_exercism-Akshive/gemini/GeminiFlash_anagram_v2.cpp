#include "anagram.h"
#include <algorithm>
#include <cctype>
#include <string>
#include <vector>
#include <unordered_map>

namespace anagram {

anagram::anagram(std::string word) : word(std::move(word)) {}

std::vector<std::string> anagram::matches(const std::vector<std::string>& words) const {
    std::string key = this->word;
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);
    std::sort(key.begin(), key.end());

    std::vector<std::string> ans;
    for (const auto& candidate : words) {
        std::string word_to_match = candidate;
        std::transform(word_to_match.begin(), word_to_match.end(), word_to_match.begin(), ::tolower);

        if (word.size() != candidate.size() || word_to_match == toLower(word)) continue;

        std::string sorted_candidate = word_to_match;
        std::sort(sorted_candidate.begin(), sorted_candidate.end());

        if (key == sorted_candidate) {
            ans.push_back(candidate);
        }
    }
    return ans;
}

std::string anagram::toLower(const std::string& s) const {
    std::string res = s;
    std::transform(res.begin(), res.end(), res.begin(), ::tolower);
    return res;
}

} // namespace anagram
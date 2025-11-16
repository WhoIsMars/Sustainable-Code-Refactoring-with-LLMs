#include "anagram.h"
#include <algorithm>
#include <string>
#include <vector>
#include <cctype>

namespace anagram {

anagram::anagram(std::string word) : word(std::move(word)) {}

std::vector<std::string> anagram::matches(const std::list<std::string>& words) {
    std::string key = this->word;
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);
    std::sort(key.begin(), key.end());

    std::vector<std::string> ans;
    for (const auto& candidate : words) {
        std::string word_to_match = candidate;
        std::transform(word_to_match.begin(), word_to_match.end(), word_to_match.begin(), ::tolower);

        if (this->word.size() != candidate.size() || this->word == candidate) continue;

        std::string sorted_candidate = word_to_match;
        std::sort(sorted_candidate.begin(), sorted_candidate.end());

        if (key == sorted_candidate) {
            ans.push_back(candidate);
        }
    }
    return ans;
}

} // namespace anagram
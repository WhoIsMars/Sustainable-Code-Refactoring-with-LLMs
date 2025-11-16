#include "anagram.h"
#include <algorithm>
#include <string>
#include <vector>
#include <cctype>

namespace anagram {

anagram::anagram(const std::string& word) : word_(word) {}

std::vector<std::string> anagram::matches(const std::vector<std::string>& words) const {
    std::string key = word_;
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);
    std::sort(key.begin(), key.end());

    std::vector<std::string> result;
    for (const auto& candidate : words) {
        std::string candidate_lower = candidate;
        std::transform(candidate_lower.begin(), candidate_lower.end(), candidate_lower.begin(), ::tolower);

        if (word_.size() != candidate.size() || word_ == candidate || candidate_lower == word_) continue;

        std::string sorted_candidate = candidate_lower;
        std::sort(sorted_candidate.begin(), sorted_candidate.end());

        if (key == sorted_candidate) {
            result.push_back(candidate);
        }
    }
    return result;
}

}  // namespace anagram
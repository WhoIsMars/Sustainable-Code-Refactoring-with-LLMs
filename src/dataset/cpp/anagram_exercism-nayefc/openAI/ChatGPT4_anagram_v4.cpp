#include "anagram.h"
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

anagram::anagram::anagram(const std::string& word) {
    this->word = word;
    this->sorted = word;
    std::transform(this->sorted.begin(), this->sorted.end(), this->sorted.begin(), ::tolower);
    std::sort(this->sorted.begin(), this->sorted.end());
}

std::vector<std::string> anagram::anagram::matches(const std::vector<std::string>& match_list) {
    std::vector<std::string> all_matches;
    for (const auto& match_word : match_list) {
        if (match_word.size() == this->word.size() && !std::equal(match_word.begin(), match_word.end(), this->word.begin(), this->word.end(), [](char a, char b) { return std::tolower(a) == std::tolower(b); }) && this->is_anagram(match_word)) {
            all_matches.push_back(match_word);
        }
    }
    return all_matches;
}

bool anagram::anagram::is_anagram(const std::string& possible_match) {
    if (possible_match.size() != this->word.size()) return false;
    std::string lower_match = possible_match;
    std::transform(lower_match.begin(), lower_match.end(), lower_match.begin(), ::tolower);
    std::sort(lower_match.begin(), lower_match.end());
    return sorted == lower_match;
}
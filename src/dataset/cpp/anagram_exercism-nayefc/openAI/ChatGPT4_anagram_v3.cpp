#include "anagram.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

anagram::anagram::anagram(std::string word) {
    this->word = word;
    this->sorted = word;
    std::transform(this->sorted.begin(), this->sorted.end(), this->sorted.begin(), ::tolower);
    std::sort(this->sorted.begin(), this->sorted.end());
}

std::vector<std::string> anagram::anagram::matches(const std::vector<std::string>& match_list) {
    std::vector<std::string> all_matches;
    all_matches.reserve(match_list.size());
    for (const auto& match_word : match_list) {
        if (this->is_anagram(match_word)) {
            std::string lower_match_word = match_word;
            std::transform(lower_match_word.begin(), lower_match_word.end(), lower_match_word.begin(), ::tolower);
            if (lower_match_word != this->word) {
                all_matches.push_back(match_word);
            }
        }
    }
    all_matches.shrink_to_fit();
    return all_matches;
}

bool anagram::anagram::is_anagram(const std::string& possible_match) {
    if (possible_match.size() != this->word.size()) return false;
    std::string sorted_match = possible_match;
    std::transform(sorted_match.begin(), sorted_match.end(), sorted_match.begin(), ::tolower);
    std::sort(sorted_match.begin(), sorted_match.end());
    return this->sorted == sorted_match;
}
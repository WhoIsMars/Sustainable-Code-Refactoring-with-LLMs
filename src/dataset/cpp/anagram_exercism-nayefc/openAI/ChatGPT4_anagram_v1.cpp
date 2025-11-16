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

std::vector<std::string> anagram::anagram::matches(std::vector<std::string> match_list) {
    std::vector<std::string> all_matches;
    for (auto &match_word : match_list) {
        std::string lower_match = match_word;
        std::transform(lower_match.begin(), lower_match.end(), lower_match.begin(), ::tolower);
        if (lower_match != this->word && this->is_anagram(lower_match)) {
            all_matches.push_back(match_word);
        }
    }
    return all_matches;
}

bool anagram::anagram::is_anagram(std::string possible_match) {
    std::transform(possible_match.begin(), possible_match.end(), possible_match.begin(), ::tolower);
    std::sort(possible_match.begin(), possible_match.end());
    return sorted == possible_match;
}
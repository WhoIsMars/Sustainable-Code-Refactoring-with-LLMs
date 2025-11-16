#include "anagram.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <unordered_map>

anagram::anagram::anagram(std::string word) : word(word) {
    sorted = word;
    boost::to_lower(sorted);
    std::sort(sorted.begin(), sorted.end());
}

std::vector<std::string> anagram::anagram::matches(std::vector<std::string> match_list) {
    std::vector<std::string> all_matches;
    all_matches.reserve(match_list.size()); // Pre-allocate memory

    std::string lower_word = word;
    boost::to_lower(lower_word);

    for (const auto &match_word : match_list) {
        if (is_anagram(match_word) && !boost::iequals(match_word, lower_word)) {
            all_matches.push_back(match_word);
        }
    }
    return all_matches;
}

bool anagram::anagram::is_anagram(const std::string& possible_match) {
    if (possible_match.length() != word.length()) {
        return false;
    }

    std::string lower_match = possible_match;
    boost::to_lower(lower_match);

    std::string sorted_match = lower_match;
    std::sort(sorted_match.begin(), sorted_match.end());

    return sorted == sorted_match;
}
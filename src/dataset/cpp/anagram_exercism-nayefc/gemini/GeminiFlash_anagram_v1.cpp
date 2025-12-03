#include "anagram.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/algorithm/string.hpp>

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
        if (!boost::iequals(match_word, word) && is_anagram(match_word)) {
            all_matches.push_back(match_word);
        }
    }
    return all_matches;
}

bool anagram::anagram::is_anagram(std::string possible_match) {
    if (possible_match.length() != word.length()) {
        return false;
    }

    std::string lower_possible_match = possible_match;
    boost::to_lower(lower_possible_match);

    std::string sorted_possible_match = lower_possible_match;
    std::sort(sorted_possible_match.begin(), sorted_possible_match.end());

    return sorted == sorted_possible_match;
}
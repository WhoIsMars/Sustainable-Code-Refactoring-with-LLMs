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
        if (match_word.length() != word.length()) continue;

        std::string lower_match_word = match_word;
        boost::to_lower(lower_match_word);

        if (lower_match_word == lower_word) continue;

        std::string sorted_match = lower_match_word;
        std::sort(sorted_match.begin(), sorted_match.end());

        if (sorted == sorted_match) {
            all_matches.push_back(match_word);
        }
    }
    return all_matches;
}
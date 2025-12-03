#include "etl.h"

#include <map>
#include <vector>
#include <algorithm>
#include <cctype>

const std::map<char, int> etl::transform(const std::map<int, std::vector<char>>& old) {
    std::map<char, int> scores;
    scores.reserve(old.size()); // Pre-allocate memory to potentially avoid reallocations

    for (const auto& [score, letters] : old) {
        for (char letter : letters) {
            char lower_letter = std::tolower(letter);
            scores[lower_letter] = score;
        }
    }

    return scores;
}
#include "etl.h"

#include <map>
#include <vector>
#include <cctype>

const std::map<char, int> etl::transform(const std::map<int, std::vector<char>>& old) {
    std::map<char, int> scores;
    scores.reserve(old.size()); // Pre-allocate memory to potentially reduce reallocations

    for (const auto& [score_value, letters] : old) {
        for (char letter : letters) {
            scores[std::tolower(letter)] = score_value;
        }
    }

    return scores;
}
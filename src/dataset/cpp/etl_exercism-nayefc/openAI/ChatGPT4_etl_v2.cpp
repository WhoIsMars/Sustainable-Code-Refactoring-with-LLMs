#include "etl.h"

#include <map>
#include <vector>
#include <locale>
#include <unordered_map>

const std::unordered_map<char, int> etl::transform(const std::map<int, std::vector<char>>& old) {
    std::unordered_map<char, int> scores;
    scores.reserve(26); // Assuming English alphabet

    for (const auto& [score, letters] : old) {
        for (char letter : letters) {
            scores[std::tolower(letter)] = score;
        }
    }

    return scores;
}
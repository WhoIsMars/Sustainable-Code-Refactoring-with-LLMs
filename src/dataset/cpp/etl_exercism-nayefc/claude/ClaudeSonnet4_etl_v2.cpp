#include "etl.h"

#include <map>
#include <vector>
#include <locale>

const std::map<char, int> etl::transform(const std::map<int, std::vector<char>>& old) {
    std::map<char, int> scores;
    scores.reserve(26); // Reserve space for typical alphabet size
    
    for (const auto& score : old) {
        const int score_value = score.first;
        for (char letter : score.second) {
            scores[std::tolower(letter)] = score_value;
        }
    }

    return scores;
}
#include "etl.h"

#include <map>
#include <vector>
#include <cctype>

const std::map<char, int> etl::transform(const std::map<int, std::vector<char>> old) {
    std::map<char, int> scores;
    scores.reserve(old.size());

    for (const auto& score : old) {
        int point_value = score.first;
        const auto& letters = score.second;
        for (char letter : letters) {
            scores[std::tolower(letter)] = point_value;
        }
    }

    return scores;
}
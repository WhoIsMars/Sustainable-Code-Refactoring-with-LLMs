#include "etl.h"

#include <map>
#include <vector>
#include <locale>

const std::map<char, int> etl::transform(const std::map<int, std::vector<char>>& old) {
    std::map<char, int> scores;
    scores.reserve(old.size() * 10);
    
    for (const auto& score : old) {
        const int point_value = score.first;
        for (char letter : score.second) {
            scores[std::tolower(letter, std::locale::classic())] = point_value;
        }
    }

    return scores;
}
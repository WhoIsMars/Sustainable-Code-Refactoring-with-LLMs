#include "etl.h"

#include <map>
#include <vector>
#include <locale>

const std::map<char, int> etl::transform(const std::map<int, std::vector<char>> old) {
    std::map<char, int> scores;
    for (const auto &score : old) {
        for (const char letter : score.second) {
            scores[std::tolower(letter)] = score.first;
        }
    }
    return scores;
}
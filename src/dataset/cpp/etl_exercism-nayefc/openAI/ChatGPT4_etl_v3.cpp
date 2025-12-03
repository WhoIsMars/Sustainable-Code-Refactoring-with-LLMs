#include "etl.h"

#include <map>
#include <vector>
#include <locale>

const std::map<char, int> etl::transform(const std::map<int, std::vector<char>> &old) {
    std::map<char, int> scores;
    for (const auto &[score, letters] : old) {
        for (char letter : letters) {
            scores[std::tolower(letter)] = score;
        }
    }
    return scores;
}
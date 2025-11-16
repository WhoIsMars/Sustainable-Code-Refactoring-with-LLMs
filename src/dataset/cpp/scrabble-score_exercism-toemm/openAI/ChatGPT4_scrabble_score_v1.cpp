#include "scrabble_score.h"

#include <unordered_map>
#include <cctype>

namespace scrabble_score {

const std::unordered_map<char, int> char_scores = {
    {'a', 1}, {'e', 1}, {'i', 1}, {'o', 1}, {'u', 1}, {'l', 1}, {'n', 1}, {'r', 1}, {'s', 1}, {'t', 1},
    {'d', 2}, {'g', 2},
    {'b', 3}, {'c', 3}, {'m', 3}, {'p', 3},
    {'f', 4}, {'h', 4}, {'v', 4}, {'w', 4}, {'y', 4},
    {'k', 5},
    {'j', 8}, {'x', 8},
    {'q', 10}, {'z', 10}
};

int score(const std::string& str) {
    int score = 0;
    for (const auto& ch : str) {
        auto it = char_scores.find(std::tolower(ch));
        if (it != char_scores.end()) {
            score += it->second;
        }
    }
    return score;
}

}  // namespace scrabble_score
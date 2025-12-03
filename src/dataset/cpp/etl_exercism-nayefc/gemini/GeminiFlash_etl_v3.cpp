#include "etl.h"

#include <map>
#include <vector>
#include <cctype>

const std::map<char, int> etl::transform(const std::map<int, std::vector<char>> old) {
    std::map<char, int> scores;
    scores.reserve(old.size());

    for (const auto& score_pair : old) {
        int score = score_pair.first;
        const std::vector<char>& letters = score_pair.second;

        for (char letter : letters) {
            char lower_letter = std::tolower(static_cast<unsigned char>(letter));
            scores[lower_letter] = score;
        }
    }

    return scores;
}
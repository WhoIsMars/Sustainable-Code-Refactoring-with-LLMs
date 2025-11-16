#include "scrabble_score.h"

#include <array>
#include <cctype>

namespace scrabble_score {

constexpr std::array<int, 26> letter_scores = {
    1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3,
    1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10
};

int score(const std::string& str) {
    int total_score = 0;
    
    for (char ch : str) {
        char lower_ch = std::tolower(ch);
        if (lower_ch >= 'a' && lower_ch <= 'z') {
            total_score += letter_scores[lower_ch - 'a'];
        }
    }
    
    return total_score;
}

}  // namespace scrabble_score
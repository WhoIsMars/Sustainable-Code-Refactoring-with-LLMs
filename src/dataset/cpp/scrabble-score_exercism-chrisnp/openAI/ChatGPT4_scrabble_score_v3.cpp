#include "scrabble_score.h"
#include <cctype>

int scrabble_score::score(const std::string& word) {
    int score = 0;
    for (char c : word) {
        if (std::isalpha(c)) {
            score += LETTER_SCORES[std::toupper(c) - 'A'];
        }
    }
    return score;
}
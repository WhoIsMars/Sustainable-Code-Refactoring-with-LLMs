#include "scrabble_score.h"
#include <cctype>

int scrabble_score::score(const std::string& word) {
    static constexpr int ASCII_OFFSET = 'A';
    int score = 0;
    for (unsigned char c : word) {
        if (std::isalpha(c)) {
            score += LETTER_SCORES[std::toupper(c) - ASCII_OFFSET];
        }
    }
    return score;
}
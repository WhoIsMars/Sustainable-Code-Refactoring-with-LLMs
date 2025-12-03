#include "scrabble_score.h"
#include <array>
#include <cctype>

constexpr std::array<int, 26> _scores = {
    1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10
};

int scrabble_score::score(const std::string& s)
{
    int sum = 0;
    for (char ch : s) {
        if (std::isalpha(ch)) {
            sum += _scores[std::toupper(ch) - 'A'];
        }
    }
    return sum;
}
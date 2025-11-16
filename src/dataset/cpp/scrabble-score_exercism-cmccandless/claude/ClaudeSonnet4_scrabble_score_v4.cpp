#include "scrabble_score.h"

static constexpr int _scores[26] = {
    1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3,
    1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10
};

int scrabble_score::score(string s)
{
    int sum = 0;
    for (char ch : s) {
        if (ch >= 'A' && ch <= 'Z') {
            sum += _scores[ch - 'A'];
        } else if (ch >= 'a' && ch <= 'z') {
            sum += _scores[ch - 'a'];
        }
    }
    return sum;
}
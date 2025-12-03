#include "scrabble_score.h"
#include <ctype.h>

unsigned int score(const char *word)
{
    static const unsigned int letter_scores[26] = {
        1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10
    };

    unsigned int score = 0;

    while (*word)
    {
        char current_char = tolower(*word);
        if (current_char >= 'a' && current_char <= 'z')
        {
            score += letter_scores[current_char - 'a'];
        }
        word++;
    }

    return score;
}
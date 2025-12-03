#include "scrabble_score.h"

#include <ctype.h>
#include <stdint.h>

static const uint8_t score_table[26] = {
    1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

unsigned int score(const char *word)
{
    unsigned int total = 0;

    for (; *word; word++)
    {
        char c = tolower(*word);
        if (c >= 'a' && c <= 'z')
        {
            total += score_table[c - 'a'];
        }
    }

    return total;
}
#include "scrabble_score.h"
#include <ctype.h>
#include <string.h>

unsigned int score(const char *word) {
    unsigned int total_score = 0;
    if (word == NULL) return 0;

    const unsigned char score_table[26] = {
        1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10
    };

    for (const char *p = word; *p != '\0'; ++p) {
        unsigned char c = (unsigned char)tolower(*p);
        if (c >= 'a' && c <= 'z') {
            total_score += score_table[c - 'a'];
        }
    }

    return total_score;
}
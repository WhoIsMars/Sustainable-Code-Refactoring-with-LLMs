#include "scrabble_score.h"
#include <ctype.h>
#include <string.h>

unsigned int score(const char *word) {
    unsigned int total_score = 0;
    if (word == NULL) return 0;

    const unsigned char letter_scores[26] = {
        1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10
    };

    for (const char *p = word; *p; ++p) {
        unsigned char c = tolower((unsigned char)*p);
        if (c >= 'a' && c <= 'z') {
            total_score += letter_scores[c - 'a'];
        }
    }

    return total_score;
}
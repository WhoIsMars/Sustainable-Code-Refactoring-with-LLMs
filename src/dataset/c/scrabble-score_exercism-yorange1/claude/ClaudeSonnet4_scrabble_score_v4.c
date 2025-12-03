#include "scrabble_score.h"

#include <ctype.h>
#include <stddef.h>
#include <stdint.h>

static const uint8_t score_table[26] = {
    1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

unsigned int score(const char *word)
{
    if (!word) return 0;
    
    unsigned int total = 0;
    const char *ptr = word;
    
    while (*ptr) {
        char c = *ptr;
        if (c >= 'A' && c <= 'Z') {
            total += score_table[c - 'A'];
        } else if (c >= 'a' && c <= 'z') {
            total += score_table[c - 'a'];
        }
        ptr++;
    }
    
    return total;
}
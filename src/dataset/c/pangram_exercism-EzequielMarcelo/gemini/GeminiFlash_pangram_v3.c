#include "pangram.h"
#include <ctype.h>
#include <stdbool.h>

bool is_pangram(const char *sentence) {
    if (sentence == NULL) {
        return false;
    }

    int seen = 0;
    int alphabet_mask = 0;

    while (*sentence) {
        char c = tolower((unsigned char)*sentence);
        if (c >= 'a' && c <= 'z') {
            int index = c - 'a';
            int bit = 1 << index;
            if (!(alphabet_mask & bit)) {
                alphabet_mask |= bit;
                seen++;
                if (seen == ALPHABET_COUNT) {
                    return true;
                }
            }
        }
        sentence++;
    }

    return seen == ALPHABET_COUNT;
}
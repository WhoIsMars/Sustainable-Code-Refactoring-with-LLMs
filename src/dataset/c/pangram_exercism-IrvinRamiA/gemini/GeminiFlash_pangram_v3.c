#include "pangram.h"
#include <stdbool.h>
#include <ctype.h>

bool is_pangram(const char *sentence) {
    if (sentence == NULL) {
        return false;
    }

    bool alphabet_present[26] = {false};
    int count = 0;

    while (*sentence) {
        unsigned char c = *sentence;
        if (isalpha(c)) {
            c = tolower(c);
            int index = c - 'a';
            if (!alphabet_present[index]) {
                alphabet_present[index] = true;
                count++;
                if (count == 26) {
                    return true;
                }
            }
        }
        sentence++;
    }

    return count == 26;
}
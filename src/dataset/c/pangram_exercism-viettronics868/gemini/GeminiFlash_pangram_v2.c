#include "pangram.h"
#include <stdbool.h>
#include <ctype.h>

bool is_pangram(const char *sentence) {
    if (sentence == NULL) {
        return false;
    }

    bool alphabet_present[26] = {false};
    int letters_found = 0;

    for (int i = 0; sentence[i] != '\0'; i++) {
        char c = tolower(sentence[i]);
        if (c >= 'a' && c <= 'z') {
            int index = c - 'a';
            if (!alphabet_present[index]) {
                alphabet_present[index] = true;
                letters_found++;
                if (letters_found == 26) {
                    return true;
                }
            }
        }
    }

    return letters_found == 26;
}
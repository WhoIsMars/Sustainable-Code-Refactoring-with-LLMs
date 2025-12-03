#include "pangram.h"
#include <stdbool.h>
#include <ctype.h>

bool is_pangram(const char *sentence) {
    if (sentence == NULL) {
        return false;
    }

    bool alphabet_present[26] = {false};
    int letters_found = 0;

    for (const char *c = sentence; *c != '\0'; ++c) {
        char lower_char = tolower(*c);
        if (lower_char >= 'a' && lower_char <= 'z') {
            int index = lower_char - 'a';
            if (!alphabet_present[index]) {
                alphabet_present[index] = true;
                letters_found++;
            }
        }
    }

    return letters_found == 26;
}
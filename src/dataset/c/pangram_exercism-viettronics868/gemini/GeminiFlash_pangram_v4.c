#include "pangram.h"
#include <stdbool.h>
#include <ctype.h>

bool is_pangram(const char *sentence) {
    if (sentence == NULL) {
        return false;
    }

    bool alphabet_present[26] = {false};
    size_t sentence_length = 0;
    while (sentence[sentence_length] != '\0') {
        unsigned char c = (unsigned char)sentence[sentence_length];
        if (isalpha(c)) {
            c = tolower(c);
            alphabet_present[c - 'a'] = true;
        }
        sentence_length++;
    }

    for (int i = 0; i < 26; i++) {
        if (!alphabet_present[i]) {
            return false;
        }
    }

    return true;
}
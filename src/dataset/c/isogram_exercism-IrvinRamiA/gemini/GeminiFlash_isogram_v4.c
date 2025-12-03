#include "isogram.h"
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool is_isogram(const char phrase[]) {
    if (phrase == NULL) {
        return false;
    }

    size_t length = strlen(phrase);
    if (length <= 1) {
        return true;
    }

    bool seen[26] = {false}; // Assuming only ASCII letters, case-insensitive

    for (size_t i = 0; i < length; i++) {
        char c = tolower(phrase[i]);
        if (isalpha(c)) {
            int index = c - 'a';
            if (seen[index]) {
                return false;
            }
            seen[index] = true;
        }
    }

    return true;
}
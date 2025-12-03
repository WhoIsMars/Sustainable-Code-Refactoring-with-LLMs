#include "isogram.h"
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool is_isogram(const char phrase[]) {
    if (phrase == NULL) {
        return false;
    }

    size_t len = strlen(phrase);
    if (len <= 1) {
        return true;
    }

    bool seen[26] = {false}; // Assuming only ASCII characters, optimize for lowercase letters

    for (size_t i = 0; i < len; i++) {
        char c = tolower(phrase[i]); // Convert to lowercase once

        if (c >= 'a' && c <= 'z') {
            int index = c - 'a';
            if (seen[index]) {
                return false; // Early exit if duplicate found
            }
            seen[index] = true;
        } else if (c == '-' || c == ' ') {
            continue; // Ignore hyphens and spaces
        }
    }

    return true;
}
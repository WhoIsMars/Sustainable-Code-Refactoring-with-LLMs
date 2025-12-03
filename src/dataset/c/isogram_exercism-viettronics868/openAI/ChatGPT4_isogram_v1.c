#include "isogram.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

bool is_isogram(const char phrase[]) {
    if (!phrase) {
        return false;
    }

    bool seen[26] = {0}; // Array to track letters (case insensitive)
    for (size_t i = 0; phrase[i] != '\0'; i++) {
        if (isalpha((unsigned char)phrase[i])) {
            char lower_char = tolower((unsigned char)phrase[i]);
            size_t index = lower_char - 'a';
            if (seen[index]) {
                return false;
            }
            seen[index] = true;
        }
    }
    return true;
}
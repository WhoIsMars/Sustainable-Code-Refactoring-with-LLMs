#include "isogram.h"
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool is_isogram(const char phrase[]) {
    if (!phrase) return false;

    bool seen[26] = {false};
    for (size_t i = 0; phrase[i] != '\0'; i++) {
        if (isalpha(phrase[i])) {
            char lower = tolower(phrase[i]);
            if (seen[lower - 'a']) return false;
            seen[lower - 'a'] = true;
        }
    }
    return true;
}
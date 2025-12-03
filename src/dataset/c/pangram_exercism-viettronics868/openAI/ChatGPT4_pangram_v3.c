#include "pangram.h"
#include <stdbool.h>
#include <stddef.h>
#include <ctype.h>

bool is_pangram(const char *sentence) {
    if (!sentence) {
        return false;
    }

    bool seen[26] = {false};
    size_t unique_count = 0;

    for (const char *ptr = sentence; *ptr != '\0'; ++ptr) {
        if (isalpha((unsigned char)*ptr)) {
            size_t index = tolower((unsigned char)*ptr) - 'a';
            if (!seen[index]) {
                seen[index] = true;
                unique_count++;
                if (unique_count == 26) {
                    return true;
                }
            }
        }
    }

    return false;
}
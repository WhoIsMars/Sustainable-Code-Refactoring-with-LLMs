#include "pangram.h"
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool is_pangram(const char *sentence) {
    if (!sentence) {
        return false;
    }

    bool alphabet[26] = {false};
    size_t unique_letters = 0;

    for (size_t i = 0; sentence[i] != '\0'; i++) {
        if (isalpha((unsigned char)sentence[i])) {
            size_t index = tolower((unsigned char)sentence[i]) - 'a';
            if (!alphabet[index]) {
                alphabet[index] = true;
                unique_letters++;
                if (unique_letters == 26) {
                    return true;
                }
            }
        }
    }

    return false;
}
#include "isogram.h"

#include <stdbool.h>
#include <stddef.h>
#include <ctype.h>

bool is_isogram(const char phrase[]) {
    if (phrase == NULL) {
        return false;
    }

    size_t len = 0;
    while (phrase[len] != '\0') {
        len++;
    }

    if (len <= 1) {
        return true;
    }

    unsigned int seen_letters = 0;

    for (size_t i = 0; i < len; ++i) {
        unsigned char c = phrase[i];
        if (isalpha(c)) {
            c = tolower(c);
            unsigned int index = c - 'a';

            if ((seen_letters & (1 << index)) != 0) {
                return false;
            }

            seen_letters |= (1 << index);
        }
    }

    return true;
}
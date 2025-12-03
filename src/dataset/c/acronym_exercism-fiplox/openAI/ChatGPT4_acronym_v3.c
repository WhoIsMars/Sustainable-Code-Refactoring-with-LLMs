#include "acronym.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char *abbreviate(const char *phrase)
{
    if (!phrase || !*phrase)
        return NULL;

    size_t len = strlen(phrase);
    char *abrev = malloc(len + 1);
    if (!abrev)
        return NULL;

    char *tmp = abrev;
    int new_word = 1;

    for (size_t i = 0; i < len; i++) {
        if (isalpha(phrase[i]) && new_word) {
            *tmp++ = toupper(phrase[i]);
            new_word = 0;
        } else if (phrase[i] == ' ' || phrase[i] == '-') {
            new_word = 1;
        }
    }

    *tmp = '\0';
    return abrev;
}
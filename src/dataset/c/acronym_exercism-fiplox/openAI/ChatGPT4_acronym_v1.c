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

    while (*phrase) {
        if (isalpha(*phrase) && new_word) {
            *tmp++ = toupper(*phrase);
            new_word = 0;
        }
        new_word = (*phrase == ' ' || *phrase == '-');
        phrase++;
    }

    *tmp = '\0';
    return abrev;
}
#include "acronym.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char *abbreviate(const char *phrase) {
    if (!phrase || !*phrase)
        return NULL;

    size_t len = strlen(phrase);
    char *abrev = malloc(len + 1);
    if (!abrev)
        return NULL;

    char *tmp = abrev;
    int add_next = 1;

    for (size_t i = 0; i < len; i++) {
        if (isalpha(phrase[i]) && add_next) {
            *tmp++ = toupper(phrase[i]);
            add_next = 0;
        }
        if (phrase[i] == ' ' || phrase[i] == '-')
            add_next = 1;
    }

    *tmp = '\0';
    return abrev;
}
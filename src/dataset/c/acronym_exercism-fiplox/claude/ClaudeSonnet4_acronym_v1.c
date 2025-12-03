#include "acronym.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *abbreviate(const char *phrase)
{
    if (!phrase || !*phrase)
        return NULL;
    
    // Calculate required size first
    size_t count = 1; // First character
    const char *p = phrase;
    while (*p) {
        if ((*p == ' ' || *p == '-') && *(p + 1) && isalpha(*(p + 1))) {
            count++;
        }
        p++;
    }
    
    char *abrev = malloc(count + 1);
    if (!abrev)
        return NULL;
    
    char *tmp = abrev;
    *tmp++ = toupper(*phrase);
    
    while (*phrase) {
        if (*phrase == ' ' || *phrase == '-') {
            phrase++;
            while (*phrase && !isalpha(*phrase))
                phrase++;
            if (*phrase)
                *tmp++ = toupper(*phrase);
        }
        if (*phrase)
            phrase++;
    }
    
    *tmp = '\0';
    return abrev;
}
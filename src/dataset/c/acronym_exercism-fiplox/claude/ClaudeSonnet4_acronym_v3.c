#include "acronym.h"

#include <ctype.h>
#include <stdio.h>
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
    *tmp++ = toupper(*phrase);
    
    for (const char *p = phrase + 1; *p; p++) {
        if ((*p == ' ' || *p == '-') && *(p + 1) && isalpha(*(p + 1))) {
            *tmp++ = toupper(*(++p));
        }
    }
    
    *tmp = '\0';
    
    size_t actual_len = tmp - abrev;
    char *result = realloc(abrev, actual_len + 1);
    return result ? result : abrev;
}
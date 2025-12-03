#include "acronym.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char *abbreviate(const char *phrase)
{
    if (!phrase || !*phrase)
        return NULL;

    size_t count = 0;
    char *result = (char *)calloc(strlen(phrase) + 1, sizeof(char));
    if (!result)
        return NULL;

    int new_word = 1;
    for (const char *p = phrase; *p; ++p)
    {
        if (isalpha(*p) && new_word)
        {
            result[count++] = toupper(*p);
            new_word = 0;
        }
        else if (*p == ' ' || *p == '-' || *p == '_')
        {
            new_word = 1;
        }
    }

    result[count] = '\0';
    return result;
}
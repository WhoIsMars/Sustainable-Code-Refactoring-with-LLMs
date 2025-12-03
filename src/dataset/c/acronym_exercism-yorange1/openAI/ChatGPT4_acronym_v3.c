#include "acronym.h"

#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *abbreviate(const char *phrase)
{
    if (!phrase || !*phrase)
        return NULL;

    size_t length = strlen(phrase);
    char *result = (char *)calloc(1, length + 1);
    if (!result)
        return NULL;

    size_t count = 0;
    int new_word = 1;

    for (size_t i = 0; i < length; i++)
    {
        if (isalpha(phrase[i]) && new_word)
        {
            result[count++] = toupper(phrase[i]);
            new_word = 0;
        }
        else if (phrase[i] == ' ' || phrase[i] == '-' || phrase[i] == '_')
        {
            new_word = 1;
        }
    }

    result[count] = '\0';
    return result;
}
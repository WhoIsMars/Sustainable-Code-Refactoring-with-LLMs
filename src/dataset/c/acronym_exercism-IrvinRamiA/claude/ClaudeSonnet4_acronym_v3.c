#include "acronym.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *abbreviate(const char *phrase)
{
    if (phrase == NULL || phrase[0] == '\0')
    {
        return NULL;
    }

    size_t phrase_len = strlen(phrase);
    char *result = (char *)malloc(phrase_len + 1);
    if (result == NULL)
    {
        return NULL;
    }

    size_t index = 0;
    result[index++] = toupper(phrase[0]);

    for (size_t i = 1; i < phrase_len; i++)
    {
        if ((phrase[i - 1] == ' ' || phrase[i - 1] == '-' || phrase[i - 1] == '_') &&
            isalpha(phrase[i]))
        {
            result[index++] = toupper(phrase[i]);
        }
    }

    result[index] = '\0';
    
    char *trimmed_result = (char *)realloc(result, index + 1);
    return trimmed_result ? trimmed_result : result;
}
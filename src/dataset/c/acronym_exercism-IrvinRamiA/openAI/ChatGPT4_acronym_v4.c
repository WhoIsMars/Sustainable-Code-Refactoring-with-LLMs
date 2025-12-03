#include "acronym.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *abbreviate(const char *phrase)
{
    if (!phrase || !*phrase)
        return NULL;

    size_t len = strlen(phrase);
    char *result = (char *)calloc(len + 1, sizeof(char));
    if (!result)
        return NULL;

    size_t index = 0;
    if (isalpha(phrase[0]))
        result[index++] = toupper(phrase[0]);

    for (size_t i = 1; i < len; i++)
    {
        if ((phrase[i - 1] == ' ' || phrase[i - 1] == '-' || phrase[i - 1] == '_') && isalpha(phrase[i]))
        {
            result[index++] = toupper(phrase[i]);
        }
    }

    result[index] = '\0';
    return result;
}
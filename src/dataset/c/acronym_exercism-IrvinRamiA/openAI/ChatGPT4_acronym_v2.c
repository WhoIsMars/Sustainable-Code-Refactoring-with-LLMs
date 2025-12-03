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

    size_t len = strlen(phrase);
    char *result = (char *)malloc(len + 1); // Allocate enough memory for worst case
    if (!result)
    {
        return NULL; // Handle memory allocation failure
    }

    size_t index = 0;

    if (isalpha(phrase[0]))
    {
        result[index++] = toupper(phrase[0]);
    }

    for (size_t i = 1; i < len; i++)
    {
        if ((phrase[i - 1] == ' ' || phrase[i - 1] == '-' || phrase[i - 1] == '_') && isalpha(phrase[i]))
        {
            result[index++] = toupper(phrase[i]);
        }
    }

    result[index] = '\0'; // Null-terminate the result
    return realloc(result, index + 1); // Resize memory to fit the result
}
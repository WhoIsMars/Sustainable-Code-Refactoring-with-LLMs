#include "acronym.h"

#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *abbreviate(const char *phrase)
{
    if (phrase == NULL || *phrase == '\0')
        return NULL;

    size_t length = strlen(phrase);
    char *result = (char *)malloc(length + 1);
    if (result == NULL)
        return NULL;

    size_t count = 0;
    int prev_was_delim = 1;

    for (size_t i = 0; i < length; i++)
    {
        char c = phrase[i];
        
        if (c == ' ' || c == '-' || c == '_')
        {
            prev_was_delim = 1;
        }
        else if (isalpha(c) && prev_was_delim)
        {
            result[count++] = toupper(c);
            prev_was_delim = 0;
        }
        else if (isalpha(c))
        {
            prev_was_delim = 0;
        }
    }

    if (count == 0)
    {
        free(result);
        return NULL;
    }

    result[count] = '\0';
    char *final_result = (char *)realloc(result, count + 1);
    return final_result ? final_result : result;
}
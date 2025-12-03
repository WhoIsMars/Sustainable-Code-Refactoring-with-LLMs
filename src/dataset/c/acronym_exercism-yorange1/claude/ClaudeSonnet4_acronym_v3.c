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
    int at_word_start = 1;

    for (size_t i = 0; i < length; i++)
    {
        char c = phrase[i];
        
        if (c == ' ' || c == '-' || c == '_')
        {
            at_word_start = 1;
        }
        else if (at_word_start && isalpha(c))
        {
            result[count++] = toupper(c);
            at_word_start = 0;
        }
        else if (isalpha(c))
        {
            at_word_start = 0;
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
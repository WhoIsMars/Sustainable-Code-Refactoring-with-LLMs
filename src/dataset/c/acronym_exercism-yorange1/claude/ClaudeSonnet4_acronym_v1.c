#include "acronym.h"

#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *abbreviate(const char *phrase)
{
    if (phrase == NULL || *phrase == '\0')
        return NULL;

    // First pass: count letters that will be in acronym
    size_t count = 0;
    int at_word_start = 1;
    
    for (const char *p = phrase; *p; p++)
    {
        if (*p == ' ' || *p == '-' || *p == '_')
        {
            at_word_start = 1;
        }
        else if (at_word_start && isalpha(*p))
        {
            count++;
            at_word_start = 0;
        }
        else if (isalpha(*p))
        {
            at_word_start = 0;
        }
    }
    
    if (count == 0)
        return NULL;

    char *result = (char *)malloc(count + 1);
    if (result == NULL)
        return NULL;

    // Second pass: build acronym
    size_t idx = 0;
    at_word_start = 1;
    
    for (const char *p = phrase; *p && idx < count; p++)
    {
        if (*p == ' ' || *p == '-' || *p == '_')
        {
            at_word_start = 1;
        }
        else if (at_word_start && isalpha(*p))
        {
            result[idx++] = toupper(*p);
            at_word_start = 0;
        }
        else if (isalpha(*p))
        {
            at_word_start = 0;
        }
    }
    
    result[count] = '\0';
    return result;
}
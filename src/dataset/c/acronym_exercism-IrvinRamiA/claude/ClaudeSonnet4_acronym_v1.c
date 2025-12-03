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

    /* Calculate phrase length once */
    size_t phrase_len = strlen(phrase);
    
    /* Allocate minimal memory based on worst case scenario */
    char *result = (char *)malloc((phrase_len + 1) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    size_t index = 0;
    
    /* Add first character if it's alphabetic */
    if (isalpha(phrase[0])) {
        result[index++] = toupper(phrase[0]);
    }

    /* Process remaining characters */
    for (size_t i = 1; i < phrase_len; i++)
    {
        if ((phrase[i - 1] == ' ' || phrase[i - 1] == '-' || phrase[i - 1] == '_') 
            && isalpha(phrase[i]))
        {
            result[index++] = toupper(phrase[i]);
        }
    }
    
    /* Null terminate and resize to actual size */
    result[index] = '\0';
    char *final_result = (char *)realloc(result, (index + 1) * sizeof(char));
    
    return final_result ? final_result : result;
}
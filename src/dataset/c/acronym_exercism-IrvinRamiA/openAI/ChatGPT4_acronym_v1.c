#include "acronym.h"
#include <stdlib.h>
#include <ctype.h>

char *abbreviate(const char *phrase)
{
    if (phrase == NULL || phrase[0] == '\0')
        return NULL;

    char *result = (char *)calloc(20, sizeof(char));
    if (!result)
        return NULL;

    char *res_ptr = result;
    if (isalpha(phrase[0]))
        *res_ptr++ = toupper(phrase[0]);

    for (const char *ptr = phrase + 1; *ptr; ++ptr)
    {
        if ((*(ptr - 1) == ' ' || *(ptr - 1) == '-' || *(ptr - 1) == '_') && isalpha(*ptr))
            *res_ptr++ = toupper(*ptr);
    }

    return result;
}
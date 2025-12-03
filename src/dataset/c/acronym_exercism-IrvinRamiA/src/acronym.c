#include "acronym.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *abbreviate(const char *phrase)
{
    /* Memory allocation to store the result */
    char *result = (char *)calloc(20, sizeof(char));

    if (phrase == NULL || phrase[0] == '\0')
    {
        /* NULL or empty string condition */
        result = NULL;
    }
    else
    {
        /* First character is stored at phrase[0] */
        unsigned char index = 0;
        *(result + index) = phrase[0];

        for (unsigned char i = 1; i < strlen(phrase); i++)
        {
            if ((phrase[i - 1] == ' ' || phrase[i - 1] == '-' ||
                 phrase[i - 1] == '_') &&
                isalpha(phrase[i]))  /*If previous character is ' ','-' or '_' then store character */
            {
                index++;
                *(result + index) = toupper(phrase[i]);
            }
        }
    }

    return result;
}

#include "bob.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

char *hey_bob(char *greeting)
{
    while (isspace(*greeting)) greeting++; // Trim leading spaces
    size_t len = strlen(greeting);
    while (len > 0 && isspace(greeting[len - 1])) len--; // Trim trailing spaces

    if (len == 0)
    {
        return strdup("Fine. Be that way!");
    }

    bool question = (greeting[len - 1] == '?');
    bool yell = false, has_letters = false;

    for (size_t i = 0; i < len; i++)
    {
        if (isalpha(greeting[i]))
        {
            has_letters = true;
            if (islower(greeting[i]))
            {
                yell = false;
                break;
            }
            yell = true;
        }
    }

    if (yell && question)
    {
        return strdup("Calm down, I know what I'm doing!");
    }
    if (yell)
    {
        return strdup("Whoa, chill out!");
    }
    if (question)
    {
        return strdup("Sure.");
    }
    return strdup("Whatever.");
}
#include "bob.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

char *hey_bob(char *greeting)
{
    bool question = false;
    bool yell = true;
    bool nothing = true;

    for (char *p = greeting; *p != '\0'; p++)
    {
        if (!isspace(*p))
            nothing = false;

        if (isalpha(*p))
        {
            if (islower(*p))
                yell = false;
        }

        if (*p == '?')
            question = (*(p + 1) == '\0' || isspace(*(p + 1)));
    }

    if (nothing)
        return strdup("Fine. Be that way!");
    if (yell && question)
        return strdup("Calm down, I know what I'm doing!");
    if (yell)
        return strdup("Whoa, chill out!");
    if (question)
        return strdup("Sure.");
    return strdup("Whatever.");
}
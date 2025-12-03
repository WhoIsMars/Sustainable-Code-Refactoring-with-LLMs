#include "bob.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

char *hey_bob(const char *greeting)
{
    bool question = false;
    bool yell = true;
    bool nothing = true;

    const char *end = greeting + strlen(greeting) - 1;

    // Trim trailing spaces
    while (end >= greeting && isspace(*end))
        end--;

    if (end < greeting) // Empty or whitespace-only input
        return strdup("Fine. Be that way!");

    if (*end == '?')
        question = true;

    for (const char *c = greeting; c <= end; c++)
    {
        if (isalpha(*c))
        {
            nothing = false;
            if (islower(*c))
                yell = false;
        }
        else if (!isspace(*c))
        {
            nothing = false;
        }
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
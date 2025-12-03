#include "bob.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

char *hey_bob(char *greeting)
{
    if (!greeting || *greeting == '\0' || strspn(greeting, " \t\n\r") == strlen(greeting))
        return strdup("Fine. Be that way!");

    size_t len = strlen(greeting);
    bool question = false, yell = false, has_lower = false;

    for (size_t i = 0; i < len; i++)
    {
        if (isalpha(greeting[i]))
        {
            if (islower(greeting[i]))
                has_lower = true;
            yell = !has_lower;
        }
    }

    if (greeting[len - 1] == '?')
        question = true;

    if (yell && question)
        return strdup("Calm down, I know what I'm doing!");
    if (yell)
        return strdup("Whoa, chill out!");
    if (question)
        return strdup("Sure.");
    return strdup("Whatever.");
}
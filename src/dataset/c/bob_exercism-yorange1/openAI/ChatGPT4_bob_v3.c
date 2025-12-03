#include "bob.h"

#define _GNU_SOURCE
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define WITHOUT_ANYTHING (0x00)
#define ANYTHING_ELSE (0x01)
#define YELL (0x03)
#define QUESTION (0x05)

char *hey_bob(char *greeting)
{
    assert(greeting != NULL);

    uint8_t flag = WITHOUT_ANYTHING;

    bool has_alpha = false;
    bool has_lower = false;
    bool has_anything = false;
    bool is_question = false;

    for (char *c = greeting; *c != '\0'; c++)
    {
        if (!isspace(*c))
        {
            has_anything = true;
        }

        if (isalpha(*c))
        {
            has_alpha = true;
            if (islower(*c))
            {
                has_lower = true;
            }
        }

        if (*c == '?')
        {
            is_question = true;
        }
    }

    if (!has_anything)
    {
        return strdup("Fine. Be that way!");
    }

    if (has_alpha && !has_lower)
    {
        flag |= YELL;
    }

    if (is_question)
    {
        flag |= QUESTION;
    }

    switch (flag)
    {
    case ANYTHING_ELSE:
        return strdup("Whatever.");
    case QUESTION:
        return strdup("Sure.");
    case YELL:
        return strdup("Whoa, chill out!");
    case YELL | QUESTION:
        return strdup("Calm down, I know what I'm doing!");
    default:
        return strdup("Whatever.");
    }
}
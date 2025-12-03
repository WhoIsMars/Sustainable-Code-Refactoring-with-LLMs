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

    for (size_t i = 0; greeting[i] != '\0'; i++)
    {
        char c = greeting[i];
        if (!isspace(c))
        {
            has_anything = true;
        }

        if (isalpha(c))
        {
            has_alpha = true;
            if (islower(c))
            {
                has_lower = true;
            }
        }

        if (c == '?')
        {
            is_question = true;
        }
        else if (!isspace(c))
        {
            is_question = false;
        }
    }

    if (!has_anything)
    {
        return strdup("Fine. Be that way!");
    }

    if (has_alpha && !has_lower)
    {
        if (is_question)
        {
            return strdup("Calm down, I know what I'm doing!");
        }
        return strdup("Whoa, chill out!");
    }

    if (is_question)
    {
        return strdup("Sure.");
    }

    return strdup("Whatever.");
}
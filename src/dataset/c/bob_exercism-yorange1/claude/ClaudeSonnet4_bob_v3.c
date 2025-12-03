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

static const char* const responses[] = {
    [WITHOUT_ANYTHING] = "Fine. Be that way!",
    [ANYTHING_ELSE] = "Whatever.",
    [QUESTION] = "Sure.",
    [YELL] = "Whoa, chill out!",
    [YELL | QUESTION] = "Calm down, I know what I'm doing!"
};

char *hey_bob(char *greeting)
{
    assert(NULL != greeting);

    uint8_t flag = WITHOUT_ANYTHING;
    bool has_alpha = false;
    bool has_lower = false;
    bool has_anything = false;
    bool is_question = false;

    for (const char *p = greeting; *p; p++)
    {
        char c = *p;
        
        if (!isspace(c))
        {
            has_anything = true;
            is_question = false;
        }

        if (isalpha(c))
        {
            has_alpha = true;
            if (islower(c))
            {
                has_lower = true;
            }
            is_question = false;
        }
        else if (c == '?')
        {
            is_question = true;
        }
    }

    if (has_anything)
        flag |= ANYTHING_ELSE;
    
    if (has_alpha && !has_lower)
        flag |= YELL;
    
    if (is_question)
        flag |= QUESTION;

    char *answer;
    asprintf(&answer, "%s", responses[flag]);
    return answer;
}
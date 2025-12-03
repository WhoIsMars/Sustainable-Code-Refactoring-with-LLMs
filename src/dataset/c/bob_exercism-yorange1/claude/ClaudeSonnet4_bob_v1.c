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
    "Fine. Be that way!",           // WITHOUT_ANYTHING (0)
    "Whatever.",                    // ANYTHING_ELSE (1)
    NULL,                          // unused (2)
    "Whoa, chill out!",            // YELL (3)
    NULL,                          // unused (4)
    "Sure.",                       // QUESTION (5)
    NULL,                          // unused (6)
    "Calm down, I know what I'm doing!" // YELL | QUESTION (7)
};

char *hey_bob(char *greeting)
{
    assert(NULL != greeting);

    uint8_t flag = WITHOUT_ANYTHING;
    bool has_alpha = false;
    bool has_lower = false;
    bool has_anything = false;
    bool is_question = false;
    
    const char *p = greeting;
    char c;
    
    while ((c = *p++)) {
        if (!isspace(c)) {
            has_anything = true;
            is_question = false;
        }
        
        if (isalpha(c)) {
            has_alpha = true;
            if (islower(c)) {
                has_lower = true;
            }
            is_question = false;
        }
        
        if (c == '?') {
            is_question = true;
        }
    }

    if (has_anything) {
        flag |= ANYTHING_ELSE;
    }

    if (has_alpha && !has_lower) {
        flag |= YELL;
    }

    if (is_question) {
        flag |= QUESTION;
    }

    const char* response = responses[flag];
    assert(response != NULL);
    
    char *answer = NULL;
    asprintf(&answer, "%s", response);
    
    return answer;
}
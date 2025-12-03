/**
 * QUESTIONS:
 * Bob answers 'Sure.' if you ask him a question, such as "How are you?".
 * He answers 'Calm down, I know what I'm doing!' if you yell a question at him.
 *
 * CAPITALLETTERS:
 * He answers 'Whoa, chill out!' if you YELL AT HIM (in all capitals).
 *
 * EMPTY:
 * He says 'Fine. Be that way!' if you address him without actually saying anything.
 *
 * ANYTHINGELSE:
 * He answers 'Whatever.' to anything else.
 */

#include "bob.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

char *hey_bob(char *greeting)
{
    char *response = (char *)malloc(65 * sizeof(char));

    bool question = false;           /* '?' at the end */
    bool yell = false;               /* Only capital letters */
    bool nothing = true;             /* Only white spaces */
    bool anything_else = false;      /* Other alphanumeric characters */
    bool previous_lower = false;     /* Greeting contains lowercase letters */

    while (*greeting != '\0')
    {
        if (isupper(*greeting) && !previous_lower)
        {
            yell = true;
            nothing = false;
        }
        else if (islower(*greeting))
        {
            previous_lower = true;
            yell = false;
            nothing = false;
        }
        else if (*greeting == '?' &&
                 (*(greeting + 1) == '\0' || *(greeting + 2) == ' '))
        {
            question = true;
            nothing = false;
        }
        else if (isspace(*greeting) && !previous_lower)
        {
            nothing = true;
        }
        else
        {
            anything_else = true;
            nothing = false;
        }

        greeting++;
    }

    /* Response assignment */
    if (nothing)
    {
        sprintf(response, "Fine. Be that way!");
    }
    else if (question && yell)
    {
        sprintf(response, "Calm down, I know what I'm doing!");
    }
    else if (question)
    {
        sprintf(response, "Sure.");
    }
    else if (yell)
    {
        sprintf(response, "Whoa, chill out!");
    }
    else if (anything_else)
    {
        sprintf(response, "Whatever.");
    }

    return response;
}

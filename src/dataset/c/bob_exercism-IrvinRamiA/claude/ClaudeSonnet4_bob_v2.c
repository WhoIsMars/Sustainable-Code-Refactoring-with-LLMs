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
#include <string.h>

static const char* const responses[] = {
    "Fine. Be that way!",
    "Sure.",
    "Whoa, chill out!",
    "Calm down, I know what I'm doing!",
    "Whatever."
};

char *hey_bob(char *greeting)
{
    bool has_letters = false;
    bool has_lowercase = false;
    bool is_question = false;
    bool has_content = false;
    
    char *ptr = greeting;
    char *last_non_space = NULL;
    
    // Single pass through the string
    while (*ptr != '\0')
    {
        if (isalpha(*ptr))
        {
            has_letters = true;
            has_content = true;
            if (islower(*ptr))
            {
                has_lowercase = true;
            }
            last_non_space = ptr;
        }
        else if (!isspace(*ptr))
        {
            has_content = true;
            last_non_space = ptr;
        }
        ptr++;
    }
    
    // Check if it's a question
    if (last_non_space && *last_non_space == '?')
    {
        is_question = true;
    }
    
    // Determine response index
    int response_idx;
    if (!has_content)
    {
        response_idx = 0; // "Fine. Be that way!"
    }
    else if (is_question && has_letters && !has_lowercase)
    {
        response_idx = 3; // "Calm down, I know what I'm doing!"
    }
    else if (is_question)
    {
        response_idx = 1; // "Sure."
    }
    else if (has_letters && !has_lowercase)
    {
        response_idx = 2; // "Whoa, chill out!"
    }
    else
    {
        response_idx = 4; // "Whatever."
    }
    
    // Allocate and copy response
    const char* selected_response = responses[response_idx];
    size_t len = strlen(selected_response) + 1;
    char *response = malloc(len);
    memcpy(response, selected_response, len);
    
    return response;
}
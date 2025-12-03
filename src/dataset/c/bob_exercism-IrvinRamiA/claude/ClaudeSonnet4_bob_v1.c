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

static const char* const RESPONSES[] = {
    "Fine. Be that way!",
    "Calm down, I know what I'm doing!",
    "Sure.",
    "Whoa, chill out!",
    "Whatever."
};

char *hey_bob(char *greeting)
{
    bool has_letters = false;
    bool has_lowercase = false;
    bool is_question = false;
    bool has_content = false;
    
    char *ptr = greeting;
    
    // Single pass through the string
    while (*ptr) {
        if (isalpha(*ptr)) {
            has_letters = true;
            has_content = true;
            if (islower(*ptr)) {
                has_lowercase = true;
            }
        } else if (*ptr == '?') {
            is_question = true;
            has_content = true;
        } else if (!isspace(*ptr)) {
            has_content = true;
        }
        ptr++;
    }
    
    // Check if question mark is at the end (ignoring trailing whitespace)
    if (is_question) {
        ptr = greeting + strlen(greeting) - 1;
        while (ptr >= greeting && isspace(*ptr)) ptr--;
        is_question = (ptr >= greeting && *ptr == '?');
    }
    
    const char* response_text;
    
    if (!has_content) {
        response_text = RESPONSES[0]; // "Fine. Be that way!"
    } else if (is_question && has_letters && !has_lowercase) {
        response_text = RESPONSES[1]; // "Calm down, I know what I'm doing!"
    } else if (is_question) {
        response_text = RESPONSES[2]; // "Sure."
    } else if (has_letters && !has_lowercase) {
        response_text = RESPONSES[3]; // "Whoa, chill out!"
    } else {
        response_text = RESPONSES[4]; // "Whatever."
    }
    
    size_t len = strlen(response_text);
    char *response = malloc(len + 1);
    memcpy(response, response_text, len + 1);
    
    return response;
}
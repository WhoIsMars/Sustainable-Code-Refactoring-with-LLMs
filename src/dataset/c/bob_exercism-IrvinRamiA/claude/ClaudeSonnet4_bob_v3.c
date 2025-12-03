#include "bob.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

char *hey_bob(char *greeting)
{
    if (!greeting) {
        char *response = malloc(24);
        strcpy(response, "Fine. Be that way!");
        return response;
    }

    bool has_letters = false;
    bool has_lowercase = false;
    bool is_question = false;
    bool is_empty = true;
    
    char *ptr = greeting;
    char *last_non_space = NULL;
    
    while (*ptr) {
        if (!isspace(*ptr)) {
            is_empty = false;
            last_non_space = ptr;
        }
        
        if (isalpha(*ptr)) {
            has_letters = true;
            if (islower(*ptr)) {
                has_lowercase = true;
            }
        }
        ptr++;
    }
    
    if (last_non_space && *last_non_space == '?') {
        is_question = true;
    }
    
    bool is_yelling = has_letters && !has_lowercase;
    
    char *response;
    
    if (is_empty) {
        response = malloc(24);
        strcpy(response, "Fine. Be that way!");
    }
    else if (is_question && is_yelling) {
        response = malloc(40);
        strcpy(response, "Calm down, I know what I'm doing!");
    }
    else if (is_question) {
        response = malloc(7);
        strcpy(response, "Sure.");
    }
    else if (is_yelling) {
        response = malloc(19);
        strcpy(response, "Whoa, chill out!");
    }
    else {
        response = malloc(10);
        strcpy(response, "Whatever.");
    }
    
    return response;
}
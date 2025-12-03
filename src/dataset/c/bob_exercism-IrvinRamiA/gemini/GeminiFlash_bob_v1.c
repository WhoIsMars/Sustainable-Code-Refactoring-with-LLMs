#include "bob.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

char *hey_bob(char *greeting) {
    bool question = false;
    bool yell = true;
    bool nothing = true;
    bool has_letter = false;
    size_t len = strlen(greeting);
    char *response = (char *)malloc(65 * sizeof(char));

    // Trim leading and trailing whitespace
    size_t start = 0;
    while (start < len && isspace(greeting[start])) {
        start++;
    }

    size_t end = len;
    while (end > start && isspace(greeting[end - 1])) {
        end--;
    }

    if (start == end) {
        sprintf(response, "Fine. Be that way!");
        return response;
    }

    // Check for yelling and question
    for (size_t i = start; i < end; i++) {
        if (isalpha(greeting[i])) {
            has_letter = true;
            if (islower(greeting[i])) {
                yell = false;
            }
            nothing = false;
        } else if (!isspace(greeting[i])) {
            nothing = false;
        }
    }

    if (greeting[end - 1] == '?') {
        question = true;
    }

    if (nothing) {
        sprintf(response, "Fine. Be that way!");
    } else if (question && yell && has_letter) {
        sprintf(response, "Calm down, I know what I'm doing!");
    } else if (question) {
        sprintf(response, "Sure.");
    } else if (yell && has_letter) {
        sprintf(response, "Whoa, chill out!");
    } else {
        sprintf(response, "Whatever.");
    }

    return response;
}
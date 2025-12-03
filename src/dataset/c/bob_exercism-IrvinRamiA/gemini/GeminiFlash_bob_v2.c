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
    bool has_letters = false;
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

    // Check for yelling and question mark, and if there are letters
    for (size_t i = start; i < end; i++) {
        if (isalpha(greeting[i])) {
            has_letters = true;
            if (islower(greeting[i])) {
                yell = false;
            }
            nothing = false;
        } else if (!isspace(greeting[i])) {
            nothing = false;
            yell = false; // Non-letter, non-space chars disqualify yelling
        }
    }

    // Check for question
    if (end > 0 && greeting[end - 1] == '?') {
        question = true;
    }

    if (nothing) {
        sprintf(response, "Fine. Be that way!");
    } else if (question && yell && has_letters) {
        sprintf(response, "Calm down, I know what I'm doing!");
    } else if (question) {
        sprintf(response, "Sure.");
    } else if (yell && has_letters) {
        sprintf(response, "Whoa, chill out!");
    } else {
        sprintf(response, "Whatever.");
    }

    return response;
}
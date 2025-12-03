#include "bob.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

char *hey_bob(char *greeting) {
    bool question = false;
    bool yell = true;
    bool has_letter = false;
    bool empty = true;
    size_t len = strlen(greeting);

    if (len == 0) {
        char *response = (char *)malloc(20);
        strcpy(response, "Fine. Be that way!");
        return response;
    }

    for (size_t i = 0; i < len; i++) {
        if (!isspace(greeting[i])) {
            empty = false;
        }

        if (islower(greeting[i])) {
            yell = false;
            has_letter = true;
        } else if (isupper(greeting[i])) {
            has_letter = true;
        } else {
            yell = false;
        }

        if (greeting[i] == '?') {
            question = true;
        }
    }

    if (empty) {
        char *response = (char *)malloc(20);
        strcpy(response, "Fine. Be that way!");
        return response;
    }

    if (question) {
        size_t i = len - 1;
        while (i > 0 && isspace(greeting[i])) {
            i--;
        }
        if (greeting[i] != '?') {
            question = false;
        }
    }

    if (yell && has_letter) {
        if (question) {
            char *response = (char *)malloc(40);
            strcpy(response, "Calm down, I know what I'm doing!");
            return response;
        } else {
            char *response = (char *)malloc(20);
            strcpy(response, "Whoa, chill out!");
            return response;
        }
    }

    if (question) {
        char *response = (char *)malloc(10);
        strcpy(response, "Sure.");
        return response;
    }

    char *response = (char *)malloc(12);
    strcpy(response, "Whatever.");
    return response;
}
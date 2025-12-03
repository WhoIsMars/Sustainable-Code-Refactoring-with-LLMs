#include "bob.h"

#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool any_alpha(const char* greeting) {
    for (int i = 0; greeting[i] != '\0'; ++i) {
        if (isalpha(greeting[i])) {
            return true;
        }
    }
    return false;
}

bool yelling(const char* greeting) {
    if (!any_alpha(greeting)) {
        return false;
    }

    for (int i = 0; greeting[i] != '\0'; ++i) {
        if (isalpha(greeting[i])) {
            if (!isupper(greeting[i])) {
                return false;
            }
        }
    }

    return true;
}

bool question(const char* greeting) {
    int len = 0;
    while (greeting[len] != '\0') {
        len++;
    }

    if (len == 0) return false;

    for (int i = len - 1; i >= 0; --i) {
        if (isspace(greeting[i])) continue;

        if (greeting[i] == '?') {
            return true;
        } else {
            return false;
        }
    }

    return false;
}


bool silence(const char* greeting) {
    for (int i = 0; greeting[i] != '\0'; ++i) {
        if (!isspace(greeting[i])) {
            return false;
        }
    }
    return true;
}

char* hey_bob(char* greeting) {
    if (silence(greeting)) {
        return "Fine. Be that way!";
    } else if (yelling(greeting)) {
        if (question(greeting)) {
            return "Calm down, I know what I'm doing!";
        } else {
            return "Whoa, chill out!";
        }
    } else if (question(greeting)) {
        return "Sure.";
    } else {
        return "Whatever.";
    }
}
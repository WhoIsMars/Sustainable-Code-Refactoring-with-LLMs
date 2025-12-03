#include "bob.h"

#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool any_alpha(const char* greeting) {
    for (const char* p = greeting; *p != '\0'; ++p) {
        if (isalpha(*p)) {
            return true;
        }
    }
    return false;
}

bool yelling(const char* greeting) {
    if (!any_alpha(greeting)) {
        return false;
    }

    for (const char* p = greeting; *p != '\0'; ++p) {
        if (isalpha(*p) && !isupper(*p)) {
            return false;
        }
    }

    return true;
}

bool question(const char* greeting) {
    size_t len = strlen(greeting);
    if (len == 0) {
        return false;
    }

    for (size_t i = len - 1; i > 0; --i) {
        if (greeting[i] == '?') {
            return true;
        } else if (isalnum(greeting[i])) {
            return false;
        }
    }
    return greeting[0] == '?';
}


bool silence(const char* greeting) {
    for (const char* p = greeting; *p != '\0'; ++p) {
        if (isalnum(*p)) {
            return false;
        }
    }
    return true;
}

char* hey_bob(char* greeting) {
    if (yelling(greeting)) {
        if (question(greeting)) {
            return "Calm down, I know what I'm doing!";
        } else {
            return "Whoa, chill out!";
        }
    } else if (question(greeting)) {
        return "Sure.";
    } else if (silence(greeting)) {
        return "Fine. Be that way!";
    } else {
        return "Whatever.";
    }
}
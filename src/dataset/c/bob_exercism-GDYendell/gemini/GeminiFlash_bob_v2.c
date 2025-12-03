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
    bool has_alpha = false;
    for (const char* p = greeting; *p != '\0'; ++p) {
        if (isalpha(*p)) {
            has_alpha = true;
            if (!isupper(*p)) {
                return false;
            }
        }
    }
    return has_alpha;
}

bool question(const char* greeting) {
    const char* p = greeting + strlen(greeting);
    while (p > greeting) {
        --p;
        if (isspace(*p)) continue;

        if (*p == '?') {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

bool silence(const char* greeting) {
    for (const char* p = greeting; *p != '\0'; ++p) {
        if (!isspace(*p)) {
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
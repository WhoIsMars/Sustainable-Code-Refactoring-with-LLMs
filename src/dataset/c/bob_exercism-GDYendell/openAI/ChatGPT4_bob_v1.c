#include "bob.h"

#include <string.h>
#include <ctype.h>

bool any_alpha(const char* greeting) {
    while (*greeting) {
        if (isalpha(*greeting)) {
            return true;
        }
        ++greeting;
    }
    return false;
}

bool yelling(const char* greeting) {
    bool has_alpha = false;
    while (*greeting) {
        if (isalpha(*greeting)) {
            has_alpha = true;
            if (!isupper(*greeting)) {
                return false;
            }
        }
        ++greeting;
    }
    return has_alpha;
}

bool question(const char* greeting) {
    const char* end = greeting + strlen(greeting) - 1;
    while (end >= greeting && isspace(*end)) {
        --end;
    }
    return end >= greeting && *end == '?';
}

bool silence(const char* greeting) {
    while (*greeting) {
        if (!isspace(*greeting)) {
            return false;
        }
        ++greeting;
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
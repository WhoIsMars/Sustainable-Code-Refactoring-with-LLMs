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
    const char* end = greeting + strlen(greeting);
    while (end > greeting && isspace(*(end - 1))) {
        --end;
    }
    return (end > greeting && *(end - 1) == '?');
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
        return question(greeting) ? "Calm down, I know what I'm doing!" : "Whoa, chill out!";
    } else if (question(greeting)) {
        return "Sure.";
    } else {
        return "Whatever.";
    }
}
#include "bob.h"

#include <string.h>
#include <ctype.h>
#include <stdbool.h>

static bool any_alpha(const char* greeting) {
    for (const char* p = greeting; *p != '\0'; ++p) {
        if (isalpha((unsigned char)*p)) {
            return true;
        }
    }
    return false;
}

static bool yelling(const char* greeting) {
    if (!any_alpha(greeting)) {
        return false;
    }

    for (const char* p = greeting; *p != '\0'; ++p) {
        if (isalpha((unsigned char)*p) && !isupper((unsigned char)*p)) {
            return false;
        }
    }

    return true;
}

static bool question(const char* greeting) {
    const char* p = greeting + strlen(greeting);
    if (p == greeting) return false;
    --p;

    while (p >= greeting && isspace((unsigned char)*p)) {
        if (p == greeting) return false;
        --p;
    }

    return *p == '?';
}

static bool silence(const char* greeting) {
    for (const char* p = greeting; *p != '\0'; ++p) {
        if (!isspace((unsigned char)*p)) {
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
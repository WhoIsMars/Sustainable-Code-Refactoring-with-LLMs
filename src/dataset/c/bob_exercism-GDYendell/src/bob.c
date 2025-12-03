#include "bob.h"

#include <string.h>
#include <ctype.h>

bool any_alpha(const char* greeting) {
    for (size_t i = 0; i < strlen(greeting); ++i) {
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

    for (size_t i = 0; i < strlen(greeting) - 1; ++i) {
        if (isalpha(greeting[i])) {
            if (!isupper(greeting[i])) {
                return false;
            }
        }
    }

    return true;
}

bool question(const char* greeting) {
    bool question_mark = false;
    for (size_t i = 0; i < strlen(greeting); ++i) {
        if (greeting[i] == '?') {
            question_mark = true;
        } else if (isalnum(greeting[i])) {
            question_mark = false;
        }
    }

    return question_mark;
}

bool silence(const char* greeting) {
    for (size_t i = 0; i < strlen(greeting); ++i) {
        if (isalnum(greeting[i])) {
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

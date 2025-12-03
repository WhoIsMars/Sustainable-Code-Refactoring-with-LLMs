#include "bob.h"

#include <string.h>
#include <ctype.h>

bool any_alpha(const char* greeting) {
    const char* ptr = greeting;
    while (*ptr) {
        if (isalpha(*ptr)) {
            return true;
        }
        ptr++;
    }
    return false;
}

bool yelling(const char* greeting) {
    const char* ptr = greeting;
    bool has_alpha = false;
    
    while (*ptr) {
        if (isalpha(*ptr)) {
            has_alpha = true;
            if (!isupper(*ptr)) {
                return false;
            }
        }
        ptr++;
    }
    
    return has_alpha;
}

bool question(const char* greeting) {
    const char* ptr = greeting;
    const char* last_question = NULL;
    
    while (*ptr) {
        if (*ptr == '?') {
            last_question = ptr;
        } else if (isalnum(*ptr)) {
            last_question = NULL;
        }
        ptr++;
    }
    
    return last_question != NULL;
}

bool silence(const char* greeting) {
    const char* ptr = greeting;
    while (*ptr) {
        if (isalnum(*ptr)) {
            return false;
        }
        ptr++;
    }
    return true;
}

char* hey_bob(char* greeting) {
    const char* ptr = greeting;
    bool has_alpha = false;
    bool is_yelling = true;
    bool has_question = false;
    bool is_silent = true;
    const char* last_question = NULL;
    
    while (*ptr) {
        if (isalpha(*ptr)) {
            has_alpha = true;
            is_silent = false;
            if (!isupper(*ptr)) {
                is_yelling = false;
            }
        } else if (isdigit(*ptr)) {
            is_silent = false;
            last_question = NULL;
        } else if (*ptr == '?') {
            last_question = ptr;
        } else if (isalnum(*ptr)) {
            is_silent = false;
            last_question = NULL;
        }
        ptr++;
    }
    
    has_question = (last_question != NULL);
    is_yelling = has_alpha && is_yelling;
    
    if (is_yelling) {
        if (has_question) {
            return "Calm down, I know what I'm doing!";
        } else {
            return "Whoa, chill out!";
        }
    } else if (has_question) {
        return "Sure.";
    } else if (is_silent) {
        return "Fine. Be that way!";
    } else {
        return "Whatever.";
    }
}
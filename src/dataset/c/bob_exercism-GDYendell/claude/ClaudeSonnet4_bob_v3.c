#include "bob.h"

#include <string.h>
#include <ctype.h>

bool any_alpha(const char* greeting) {
    for (const char* p = greeting; *p; ++p) {
        if (isalpha(*p)) {
            return true;
        }
    }
    return false;
}

bool yelling(const char* greeting) {
    bool has_alpha = false;
    
    for (const char* p = greeting; *p; ++p) {
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
        if (*p == '?') {
            return true;
        } else if (isalnum(*p)) {
            return false;
        }
    }
    
    return false;
}

bool silence(const char* greeting) {
    for (const char* p = greeting; *p; ++p) {
        if (isalnum(*p)) {
            return false;
        }
    }
    return true;
}

char* hey_bob(char* greeting) {
    bool is_yelling = yelling(greeting);
    bool is_question = question(greeting);
    
    if (is_yelling) {
        if (is_question) {
            return "Calm down, I know what I'm doing!";
        } else {
            return "Whoa, chill out!";
        }
    } else if (is_question) {
        return "Sure.";
    } else if (silence(greeting)) {
        return "Fine. Be that way!";
    } else {
        return "Whatever.";
    }
}
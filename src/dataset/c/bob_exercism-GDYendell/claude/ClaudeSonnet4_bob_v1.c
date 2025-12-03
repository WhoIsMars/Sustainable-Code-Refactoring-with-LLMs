#include "bob.h"

#include <string.h>
#include <ctype.h>

char* hey_bob(char* greeting) {
    size_t len = strlen(greeting);
    bool has_alpha = false;
    bool is_yelling = true;
    bool is_question = false;
    bool is_silence = true;
    
    // Single pass through the string
    for (size_t i = 0; i < len; ++i) {
        char c = greeting[i];
        
        if (isalpha(c)) {
            has_alpha = true;
            is_silence = false;
            if (!isupper(c)) {
                is_yelling = false;
            }
        } else if (isdigit(c)) {
            is_silence = false;
        }
        
        if (c == '?') {
            is_question = true;
        } else if (isalnum(c)) {
            is_question = false;
        }
    }
    
    // Adjust yelling based on whether there are alphabetic characters
    is_yelling = is_yelling && has_alpha;
    
    if (is_yelling) {
        if (is_question) {
            return "Calm down, I know what I'm doing!";
        } else {
            return "Whoa, chill out!";
        }
    } else if (is_question) {
        return "Sure.";
    } else if (is_silence) {
        return "Fine. Be that way!";
    } else {
        return "Whatever.";
    }
}

bool any_alpha(const char* greeting) {
    size_t len = strlen(greeting);
    for (size_t i = 0; i < len; ++i) {
        if (isalpha(greeting[i])) {
            return true;
        }
    }
    return false;
}

bool yelling(const char* greeting) {
    size_t len = strlen(greeting);
    bool has_alpha = false;
    
    for (size_t i = 0; i < len; ++i) {
        if (isalpha(greeting[i])) {
            has_alpha = true;
            if (!isupper(greeting[i])) {
                return false;
            }
        }
    }
    
    return has_alpha;
}

bool question(const char* greeting) {
    size_t len = strlen(greeting);
    bool question_mark = false;
    
    for (size_t i = 0; i < len; ++i) {
        if (greeting[i] == '?') {
            question_mark = true;
        } else if (isalnum(greeting[i])) {
            question_mark = false;
        }
    }
    
    return question_mark;
}

bool silence(const char* greeting) {
    size_t len = strlen(greeting);
    for (size_t i = 0; i < len; ++i) {
        if (isalnum(greeting[i])) {
            return false;
        }
    }
    return true;
}
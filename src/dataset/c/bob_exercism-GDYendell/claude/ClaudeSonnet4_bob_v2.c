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
        } else if (c == '?') {
            is_question = true;
        } else if (isalnum(c)) {
            is_question = false;
            is_silence = false;
        }
    }
    
    // Adjust yelling based on presence of alphabetic characters
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
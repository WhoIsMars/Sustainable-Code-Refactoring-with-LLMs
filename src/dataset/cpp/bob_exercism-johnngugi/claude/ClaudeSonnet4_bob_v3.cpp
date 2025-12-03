#include "bob.h"
#include <string>
#include <cctype>

std::string bob::hey(std::string statement)
{
    if (statement.empty()) {
        return "Fine. Be that way!";
    }

    bool has_alpha = false;
    bool has_non_upper = false;
    bool has_non_space = false;
    
    // Single pass through the string
    for (char c : statement) {
        if (std::isalpha(c)) {
            has_alpha = true;
            if (!std::isupper(c)) {
                has_non_upper = true;
            }
        }
        if (!std::isspace(c)) {
            has_non_space = true;
        }
    }
    
    // Check if only whitespace
    if (!has_non_space) {
        return "Fine. Be that way!";
    }
    
    // Check if yelling (all uppercase with at least one letter)
    if (has_alpha && !has_non_upper) {
        return "Whoa, chill out!";
    }
    
    // Check if question (look for '?' from the end, ignoring trailing whitespace)
    for (auto it = statement.rbegin(); it != statement.rend(); ++it) {
        if (*it == '?') {
            return "Sure.";
        }
        if (!std::isspace(*it)) {
            break;
        }
    }
    
    return "Whatever.";
}
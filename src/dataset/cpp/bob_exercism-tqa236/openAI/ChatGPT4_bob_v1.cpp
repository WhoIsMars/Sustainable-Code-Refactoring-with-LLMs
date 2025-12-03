#include "bob.h"
#include <algorithm>
#include <cctype>

std::string bob::hey(std::string text) {
    bool has_uppercase = false;
    bool has_lowercase = false;
    bool is_question = false;

    text.erase(std::remove_if(text.begin(), text.end(), ::isspace), text.end());
    if (text.empty()) {
        return "Fine. Be that way!";
    }

    for (char c : text) {
        if (std::isupper(c)) has_uppercase = true;
        if (std::islower(c)) has_lowercase = true;
    }

    is_question = text.back() == '?';
    bool is_yelling = has_uppercase && !has_lowercase;

    if (is_yelling && is_question) {
        return "Calm down, I know what I'm doing!";
    }
    if (is_yelling) {
        return "Whoa, chill out!";
    }
    if (is_question) {
        return "Sure.";
    }
    return "Whatever.";
}
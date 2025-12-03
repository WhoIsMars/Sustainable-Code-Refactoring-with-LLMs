#include "bob.h"
#include <algorithm>
#include <cctype>

std::string bob::hey(std::string text) {
    text.erase(std::remove_if(text.begin(), text.end(), ::isspace), text.end());
    if (text.empty()) {
        return "Fine. Be that way!";
    }

    bool has_uppercase = std::any_of(text.begin(), text.end(), ::isupper);
    bool has_lowercase = std::any_of(text.begin(), text.end(), ::islower);
    bool is_yelling = has_uppercase && !has_lowercase;
    bool is_question = text.back() == '?';

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
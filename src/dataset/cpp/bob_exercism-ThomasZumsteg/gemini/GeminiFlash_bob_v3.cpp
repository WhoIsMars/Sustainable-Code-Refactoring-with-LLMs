#include "bob.h"

#include <algorithm>
#include <cctype>
#include <string>

namespace bob {

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return "";
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

bool is_yelling(const std::string& phrase) {
    bool has_letters = false;
    for (char c : phrase) {
        if (std::isalpha(c)) {
            has_letters = true;
            break;
        }
    }

    if (!has_letters) {
        return false;
    }

    for (char c : phrase) {
        if (std::isalpha(c) && std::islower(c)) {
            return false;
        }
    }

    return true;
}

std::string response(const std::string& phrase) {
    std::string trimmed_phrase = trim(phrase);

    if (trimmed_phrase.empty()) {
        return "Fine. Be that way!";
    }

    bool yelling = is_yelling(trimmed_phrase);
    bool question = !trimmed_phrase.empty() && trimmed_phrase.back() == '?';

    if (yelling && question) {
        return "Calm down, I know what I'm doing!";
    } else if (yelling) {
        return "Whoa, chill out!";
    } else if (question) {
        return "Sure.";
    } else {
        return "Whatever.";
    }
}

} // namespace bob
#include "acronym.h"
#include <cctype>
#include <string>

std::string acronym::acronym(const std::string &_phrase) noexcept {
    std::string acro;
    bool boundary = true;

    for (char ch : _phrase) {
        if (boundary && std::isalnum(ch)) {
            acro += std::toupper(ch);
            boundary = false;
        } else if (ch == ' ' || ch == '_' || ch == '-') {
            boundary = true;
        }
    }

    return acro;
}
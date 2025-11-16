#include "acronym.h"
#include <cctype>

std::string acronym::acronym(const std::string &_phrase) noexcept {
    std::string acro;
    acro.reserve(_phrase.size());
    bool boundary = true;

    for (char ch : _phrase) {
        if (std::isalnum(ch)) {
            if (boundary) {
                acro += std::toupper(ch);
                boundary = false;
            }
        } else if (ch == ' ' || ch == '_' || ch == '-') {
            boundary = true;
        }
    }

    return acro;
}
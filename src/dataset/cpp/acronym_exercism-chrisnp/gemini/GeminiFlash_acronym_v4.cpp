#include "acronym.h"
#include <algorithm>
#include <cctype>

std::string acronym::acronym(const std::string &_phrase) noexcept {
    std::string acro;
    acro.reserve(_phrase.length() / 2); // Pre-allocate space to avoid reallocations
    bool boundary = true;

    for (size_t i = 0; i < _phrase.length(); ++i) {
        char ch = _phrase[i];
        if (isalnum(ch) && boundary) {
            acro += toupper(ch);
            boundary = false;
        } else if (ch == ' ' || ch == '_' || ch == '-') {
            boundary = true;
        }
    }
    return acro;
}
#include "acronym.h"

std::string acronym::acronym(const std::string &_phrase) noexcept {
    std::string acro;
    acro.reserve(_phrase.length() / 4); // Reserve approximate space
    bool boundary = true;
    
    for (char ch : _phrase) {
        if (isalnum(ch) && boundary) {
            acro += static_cast<char>(toupper(ch));
            boundary = false;
        } else if (ch == ' ' || ch == '_' || ch == '-') {
            boundary = true;
        }
    }
    return acro;
}
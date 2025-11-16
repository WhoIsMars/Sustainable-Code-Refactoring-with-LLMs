#include "acronym.h"

std::string acronym::acronym(const std::string &_phrase) noexcept {
    std::string acro;
    acro.reserve(_phrase.length() / 4); // Reserve estimated capacity
    bool boundary = true;
    
    for (char ch : _phrase) {
        if (boundary && std::isalnum(static_cast<unsigned char>(ch))) {
            acro += std::toupper(static_cast<unsigned char>(ch));
            boundary = false;
        } else if (ch == ' ' || ch == '_' || ch == '-') {
            boundary = true;
        }
    }
    return acro;
}
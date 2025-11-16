#include "acronym.h"

std::string acronym::acronym(const std::string &_phrase) noexcept {
    std::string acro;
    acro.reserve(_phrase.length() / 4);
    
    bool boundary = true;
    
    for (char ch : _phrase) {
        if (std::isalnum(ch) && boundary) {
            acro += std::toupper(ch);
            boundary = false;
        } else if (ch == ' ' || ch == '_' || ch == '-') {
            boundary = true;
        }
    }
    
    return acro;
}
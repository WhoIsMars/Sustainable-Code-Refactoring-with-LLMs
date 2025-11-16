#include "acronym.h"

std::string acronym::acronym(const std::string &_phrase) noexcept {
    std::string acro { "" };
    bool boundary { true };
    // word boundaries
    char _bounds[] = {' ', '_', '-'};
    for (auto ch : _phrase) {
        if (isalnum(ch) && boundary) {
            acro += toupper(ch);
            boundary = false;
        } 
        // check if ch is in word boundaries
        char *it { std::find(std::begin(_bounds), std::end(_bounds), ch) };
        // if it is, switch boundary truth
        if (it != std::end(_bounds)) boundary = true;
    }
    return acro;
}

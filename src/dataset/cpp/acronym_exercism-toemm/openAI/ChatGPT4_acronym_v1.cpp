#include "acronym.h"

#include <cctype>

namespace acronym {

std::string acronym(const std::string& sentence) {
    std::string acronym;
    bool new_word = true;

    for (char ch : sentence) {
        if (std::isalpha(ch)) {
            if (new_word) {
                acronym.push_back(std::toupper(ch));
                new_word = false;
            }
        } else {
            new_word = (ch == ' ' || ch == '-');
        }
    }

    return acronym;
}

}  // namespace acronym
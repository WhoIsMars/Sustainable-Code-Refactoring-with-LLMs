#include "acronym.h"

#include <cctype>
#include <string>

namespace acronym {

std::string acronym(const std::string& sentence) {
    std::string result;
    bool new_word = true;

    for (char ch : sentence) {
        if (std::isalpha(ch)) {
            if (new_word) {
                result.push_back(std::toupper(ch));
                new_word = false;
            }
        } else {
            new_word = (ch == ' ' || ch == '-');
        }
    }

    return result;
}

}  // namespace acronym
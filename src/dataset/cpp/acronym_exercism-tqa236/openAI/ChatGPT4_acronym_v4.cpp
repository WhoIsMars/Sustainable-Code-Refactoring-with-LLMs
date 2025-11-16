#include "acronym.h"
#include <cctype>

std::string acronym::acronym(const std::string& name) {
    std::string acronym_name;
    acronym_name.reserve(name.size() / 2); // Reserve approximate space to reduce reallocations
    bool flag = true;
    for (char c : name) {
        if (std::isalpha(c)) {
            if (flag) {
                acronym_name += std::toupper(c);
                flag = false;
            }
        } else {
            flag = true;
        }
    }
    return acronym_name;
}
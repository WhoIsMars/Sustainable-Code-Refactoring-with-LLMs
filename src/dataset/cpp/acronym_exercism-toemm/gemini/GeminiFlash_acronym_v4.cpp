#include "acronym.h"

#include <algorithm>
#include <cctype>
#include <sstream>

namespace acronym {

std::string acronym(const std::string& sentence) {
    std::string acronym;
    std::istringstream iss(sentence);
    std::string word;

    while (iss >> word) {
        if (!word.empty()) {
            // Find the first alphabetic character
            auto it = std::find_if(word.begin(), word.end(), ::isalpha);
            if (it != word.end()) {
                acronym += std::toupper(*it);
            }
        }
    }

    return acronym;
}

}  // namespace acronym
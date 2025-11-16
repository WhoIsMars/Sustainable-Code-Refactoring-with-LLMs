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
        // Remove non-alphabetic characters from the beginning of the word
        word.erase(0, std::distance(word.begin(), std::find_if(word.begin(), word.end(), ::isalpha)));

        if (!word.empty()) {
            acronym += std::toupper(word[0]);
        }
    }

    return acronym;
}

}  // namespace acronym
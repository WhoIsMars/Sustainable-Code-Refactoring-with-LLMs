#include "acronym.h"

#include <algorithm>

namespace acronym {

std::string acronym(const std::string& sentence) {
    std::string result;
    result.reserve(sentence.length() / 4); // Estimate capacity to reduce reallocations
    
    bool new_word = true;
    
    for (char ch : sentence) {
        if (ch == '-' || ch == ' ') {
            new_word = true;
        } else if (std::isalpha(static_cast<unsigned char>(ch))) {
            if (new_word) {
                result.push_back(std::toupper(static_cast<unsigned char>(ch)));
                new_word = false;
            }
        }
    }
    
    return result;
}

}  // namespace acronym
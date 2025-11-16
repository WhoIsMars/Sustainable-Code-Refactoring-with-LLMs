#include "acronym.h"

#include <cctype>

namespace acronym {

std::string acronym(const std::string& sentence) {
    std::string result;
    result.reserve(sentence.length() / 4);
    
    bool new_word = true;
    
    for (char ch : sentence) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            if (new_word) {
                result.push_back(std::toupper(static_cast<unsigned char>(ch)));
                new_word = false;
            }
        } else if (ch == ' ' || ch == '-') {
            new_word = true;
        }
    }
    
    return result;
}

}  // namespace acronym
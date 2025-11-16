#include "acronym.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

namespace acronym {

std::string acronym(const std::string& sentence) {
    std::string result;
    result.reserve(sentence.size() / 2); // Pre-allocate memory to avoid reallocations

    bool new_word = true;
    for (size_t i = 0; i < sentence.size(); ++i) {
        char ch = sentence[i];

        if (isalpha(ch)) {
            if (new_word) {
                result.push_back(toupper(ch));
                new_word = false;
            }
        } else if (ch == '-' || ch == ' ') {
            new_word = true;
        } else {
            // Ignore other characters
        }
    }

    return result;
}

}  // namespace acronym
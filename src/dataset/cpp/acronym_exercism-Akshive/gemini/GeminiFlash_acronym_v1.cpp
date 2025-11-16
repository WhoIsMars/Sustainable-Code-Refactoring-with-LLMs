#include "acronym.h"
#include <string>
#include <cctype>

namespace acronym {
    std::string acronym(std::string str) {
        std::string ans;
        ans.reserve(str.length() / 2); // Pre-allocate memory to avoid reallocations

        bool newWord = true;
        for (char c : str) {
            if (std::isalpha(c)) {
                if (newWord) {
                    ans.push_back(std::toupper(c));
                    newWord = false;
                }
            } else {
                newWord = true;
            }
        }
        return ans;
    }
}  // namespace acronym
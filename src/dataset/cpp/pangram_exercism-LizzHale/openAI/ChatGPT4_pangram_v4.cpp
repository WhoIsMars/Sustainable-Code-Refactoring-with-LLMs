#include "pangram.h"
#include <unordered_set>
#include <cctype>

namespace pangram {

    bool is_pangram(const std::string& sentence) {
        std::unordered_set<char> letters;
        for (char c : sentence) {
            if (std::isalpha(c)) {
                letters.insert(std::tolower(c));
                if (letters.size() == 26) {
                    return true;
                }
            }
        }
        return false;
    }

}  // namespace pangram
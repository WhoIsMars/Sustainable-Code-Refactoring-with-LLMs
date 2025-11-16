#include "pangram.h"
#include <unordered_set>
#include <cctype>

namespace pangram {

    bool is_pangram(const std::string& sentence) {
        std::unordered_set<char> seen_letters;
        for (char c : sentence) {
            if (std::isalpha(c)) {
                seen_letters.insert(std::tolower(c));
                if (seen_letters.size() == 26) {
                    return true;
                }
            }
        }
        return seen_letters.size() == 26;
    }

}  // namespace pangram
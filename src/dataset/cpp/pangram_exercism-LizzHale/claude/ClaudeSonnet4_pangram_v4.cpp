#include "pangram.h"
#include <bitset>
#include <cctype>

namespace pangram {

    bool is_pangram(std::string sentence) {
        std::bitset<26> letters;
        
        for (char c : sentence) {
            if (std::isalpha(c)) {
                letters[std::tolower(c) - 'a'] = true;
            }
        }
        
        return letters.all();
    }

    bool is_in_sentence(char character, std::string sentence) {
        char lower_char = std::tolower(character);
        for (char c : sentence) {
            if (std::tolower(c) == lower_char) {
                return true;
            }
        }
        return false;
    }

}  // namespace pangram
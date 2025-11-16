#include "pangram.h"
#include <bitset>
#include <cctype>

namespace pangram {

    bool is_pangram(const std::string& sentence) {
        std::bitset<26> letters_found;
        
        for (char c : sentence) {
            if (std::isalpha(c)) {
                letters_found[std::tolower(c) - 'a'] = true;
                if (letters_found.all()) {
                    return true;
                }
            }
        }
        
        return letters_found.all();
    }

    bool is_in_sentence(char character, const std::string& sentence) {
        char lower_char = std::tolower(character);
        for (char c : sentence) {
            if (std::tolower(c) == lower_char) {
                return true;
            }
        }
        return false;
    }

}  // namespace pangram
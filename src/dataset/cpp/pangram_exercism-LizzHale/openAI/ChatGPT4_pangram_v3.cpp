#include "pangram.h"
#include <unordered_set>
#include <algorithm>

namespace pangram {

    bool is_pangram(std::string sentence) {
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

    bool is_in_sentence(char character, std::string sentence) {
        character = std::tolower(character);
        return std::any_of(sentence.begin(), sentence.end(), [character](char c) {
            return std::tolower(c) == character;
        });
    }

}  // namespace pangram
#include "pangram.h"

namespace pangram {

    bool is_pangram(std::string sentence) {
        for (int a = 97; a < 123; ++a ) {
            if (is_in_sentence(char(a), sentence)) {
                continue;
            }
            return false;
        }
        return true;
    }

    bool is_in_sentence(char character, std::string sentence) {
        for (int i = sentence.length(); i >0; --i) {
            if (character == tolower(sentence[i])) {
                return true;
            }
            continue;
        }
        return false;
    }

}  // namespace pangram

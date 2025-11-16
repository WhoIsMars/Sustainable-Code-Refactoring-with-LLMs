#include <string>
#include <cctype>

namespace pangram {
    bool is_pangram(const std::string& text) {
        if (text.length() < 26) return false;

        std::bitset<26> alphabet_flags;

        for (char ch : text) {
            if (std::islower(ch)) {
                alphabet_flags.set(ch - 'a');
            } else if (std::isupper(ch)) {
                alphabet_flags.set(ch - 'A');
            }
        }

        return alphabet_flags.all();
    }
}
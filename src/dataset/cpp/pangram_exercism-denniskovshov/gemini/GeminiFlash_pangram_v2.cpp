#include <string>
#include <cctype>

namespace pangram {
    bool is_pangram(const std::string& text) {
        if (text.length() < 26) return false;

        std::bitset<26> flags;

        for (char ch : text) {
            if (std::islower(ch)) {
                flags.set(ch - 'a');
            } else if (std::isupper(ch)) {
                flags.set(ch - 'A');
            }
        }

        return flags.all();
    }
}
#include <cctype>
#include <string>
#include <algorithm>

namespace pangram {

bool is_pangram(const std::string& text) {
    if (text.length() < 26) return false;

    std::bitset<26> flags;
    for (unsigned char ch : text) {
        if (std::isalpha(ch)) {
            flags.set(std::tolower(ch) - 'a');
        }
    }

    return flags.all();
}

}  // namespace pangram
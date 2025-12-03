#include <string>
#include <algorithm>
#include <cctype>

namespace pangram {

bool is_pangram(const std::string& text) {
    if (text.length() < 26) return false;

    std::bitset<26> flags;
    for (char ch : text) {
        if (std::isalpha(ch)) {
            char lower_ch = std::tolower(ch);
            flags.set(lower_ch - 'a');
        }
    }

    return flags.all();
}

}  // namespace pangram
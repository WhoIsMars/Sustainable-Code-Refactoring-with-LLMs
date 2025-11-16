#include "atbash_cipher.h"
#include <algorithm>
#include <cctype>

namespace atbash_cipher {

std::string encode(const std::string& msg) {
    std::string out;
    out.reserve(msg.length() * 2); // Pre-allocate memory

    int ctr = 0;
    for (char ch : msg) {
        if (std::isalpha(ch)) {
            char lower_ch = std::tolower(ch);
            if (ctr > 0 && ctr % 5 == 0) {
                out += ' ';
            }
            out += static_cast<char>('a' + 'z' - lower_ch);
            ctr++;
        } else if (std::isdigit(ch)) {
            if (ctr > 0 && ctr % 5 == 0) {
                out += ' ';
            }
            out += ch;
            ctr++;
        }
    }
    return out;
}

std::string decode(const std::string& msg) {
    std::string out;
    out.reserve(msg.length()); // Pre-allocate memory

    for (char ch : msg) {
        if (std::isalpha(ch)) {
            out += static_cast<char>('a' + ('z' - std::tolower(ch)));
        } else if (std::isdigit(ch)) {
            out += ch;
        }
    }
    return out;
}

}  // namespace atbash_cipher
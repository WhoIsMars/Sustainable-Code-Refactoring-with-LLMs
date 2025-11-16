#include "atbash_cipher.h"
#include <algorithm>
#include <cctype>

namespace atbash_cipher {

std::string encode(const std::string& msg) {
    std::string out;
    out.reserve(msg.length() * 1.2); // Pre-allocate space to avoid reallocations

    int ctr = 0;
    for (char ch : msg) {
        if (std::isalnum(ch)) {
            if (ctr > 0 && ctr % 5 == 0) {
                out += ' ';
            }

            if (std::isalpha(ch)) {
                out += 'a' + 'z' - std::tolower(ch);
            } else {
                out += ch;
            }
            ctr++;
        }
    }
    return out;
}

std::string decode(const std::string& msg) {
    std::string out;
    out.reserve(msg.length()); // Pre-allocate space

    for (char ch : msg) {
        if (std::isalnum(ch)) {
            if (std::isalpha(ch)) {
                out += 'a' + ('z' - ch);
            } else {
                out += ch;
            }
        }
    }
    return out;
}

}  // namespace atbash_cipher
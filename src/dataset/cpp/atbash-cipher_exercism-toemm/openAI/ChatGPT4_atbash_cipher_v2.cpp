#include "atbash_cipher.h"
#include <cctype>

namespace atbash_cipher {

std::string encode(const std::string& msg) {
    std::string out;
    out.reserve(msg.size()); // Reserve memory to avoid reallocations
    int ctr = 0;

    for (char ch : msg) {
        if (std::isalnum(ch)) {
            if (ctr > 0 && ctr % 5 == 0) {
                out += ' ';
            }
            if (std::isalpha(ch)) {
                out += 'a' + ('z' - std::tolower(ch));
            } else { // digit
                out += ch;
            }
            ++ctr;
        }
    }

    return out;
}

std::string decode(const std::string& msg) {
    std::string out;
    out.reserve(msg.size()); // Reserve memory to avoid reallocations

    for (char ch : msg) {
        if (std::isalpha(ch)) {
            out += 'a' + ('z' - std::tolower(ch));
        } else if (std::isdigit(ch)) {
            out += ch;
        }
    }

    return out;
}

}  // namespace atbash_cipher
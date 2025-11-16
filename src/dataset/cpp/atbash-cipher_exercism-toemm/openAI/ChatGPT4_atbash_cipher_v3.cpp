#include "atbash_cipher.h"
#include <cctype>
#include <string>

namespace atbash_cipher {

std::string encode(const std::string& msg) {
    std::string out;
    out.reserve(msg.size() + msg.size() / 5); // Reserve memory to minimize reallocations
    int ctr = 0;

    for (char ch : msg) {
        if (std::isalpha(ch)) {
            if (ctr && ctr % 5 == 0) out += ' ';
            out += 'z' - (std::tolower(ch) - 'a');
            ++ctr;
        } else if (std::isdigit(ch)) {
            if (ctr && ctr % 5 == 0) out += ' ';
            out += ch;
            ++ctr;
        }
    }

    return out;
}

std::string decode(const std::string& msg) {
    std::string out;
    out.reserve(msg.size()); // Reserve memory to minimize reallocations

    for (char ch : msg) {
        if (std::isalpha(ch)) {
            out += 'z' - (std::tolower(ch) - 'a');
        } else if (std::isdigit(ch)) {
            out += ch;
        }
    }

    return out;
}

}  // namespace atbash_cipher
#include "atbash_cipher.h"

namespace atbash_cipher {

std::string encode(const std::string& msg) {
    std::string out;
    out.reserve(msg.length() + msg.length() / 4);
    
    int ctr = 0;
    
    for (char ch : msg) {
        if (std::isalpha(ch)) {
            if (ctr % 5 == 0 && ctr > 0) {
                out += ' ';
            }
            out += static_cast<char>(219 - std::tolower(ch));
            ++ctr;
        } else if (std::isdigit(ch)) {
            if (ctr % 5 == 0 && ctr > 0) {
                out += ' ';
            }
            out += ch;
            ++ctr;
        }
    }
    
    return out;
}

std::string decode(const std::string& msg) {
    std::string out;
    out.reserve(msg.length());
    
    for (char ch : msg) {
        if (std::isalpha(ch)) {
            out += static_cast<char>(219 - std::tolower(ch));
        } else if (std::isdigit(ch)) {
            out += ch;
        }
    }
    
    return out;
}

}  // namespace atbash_cipher
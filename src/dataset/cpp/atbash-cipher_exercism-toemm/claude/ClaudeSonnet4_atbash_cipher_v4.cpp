#include "atbash_cipher.h"

namespace atbash_cipher {

std::string encode(const std::string& msg) {
    std::string out;
    out.reserve(msg.length() + msg.length() / 4);
    
    int ctr = 0;
    
    for (char ch : msg) {
        if (ch >= 'A' && ch <= 'Z') {
            if (ctr % 5 == 0 && ctr > 0) out += ' ';
            out += static_cast<char>(219 - ch);
            ++ctr;
        }
        else if (ch >= 'a' && ch <= 'z') {
            if (ctr % 5 == 0 && ctr > 0) out += ' ';
            out += static_cast<char>(219 - ch);
            ++ctr;
        }
        else if (ch >= '0' && ch <= '9') {
            if (ctr % 5 == 0 && ctr > 0) out += ' ';
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
        if (ch >= 'a' && ch <= 'z') {
            out += static_cast<char>(219 - ch);
        }
        else if (ch >= '0' && ch <= '9') {
            out += ch;
        }
    }
    
    return out;
}

}  // namespace atbash_cipher
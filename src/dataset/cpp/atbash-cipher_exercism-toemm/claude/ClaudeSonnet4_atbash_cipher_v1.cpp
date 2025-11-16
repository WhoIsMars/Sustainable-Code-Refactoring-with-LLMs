#include "atbash_cipher.h"

namespace atbash_cipher {

std::string encode(const std::string& msg) {
    std::string out;
    out.reserve(msg.length() + msg.length() / 4); // Reserve space for output + spaces
    
    int ctr = 0;
    
    for (char ch : msg) {
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            if (ctr % 5 == 0 && ctr > 0) out += ' ';
            
            char lower_ch = (ch >= 'A' && ch <= 'Z') ? ch + 32 : ch;
            out += static_cast<char>(219 - lower_ch); // 97 + 122 = 219
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
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            char lower_ch = (ch >= 'A' && ch <= 'Z') ? ch + 32 : ch;
            out += static_cast<char>(219 - lower_ch);
        }
        else if (ch >= '0' && ch <= '9') {
            out += ch;
        }
    }
    
    return out;
}

}  // namespace atbash_cipher
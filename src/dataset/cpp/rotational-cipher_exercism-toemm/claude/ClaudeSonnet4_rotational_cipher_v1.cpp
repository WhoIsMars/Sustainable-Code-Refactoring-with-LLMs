#include "rotational_cipher.h"

namespace rotational_cipher {

std::string rotate(std::string in, int shift) {
    shift = ((shift % 26) + 26) % 26;
    
    for (char& ch : in) {
        if (ch >= 'A' && ch <= 'Z') {
            ch = 'A' + (ch - 'A' + shift) % 26;
        } else if (ch >= 'a' && ch <= 'z') {
            ch = 'a' + (ch - 'a' + shift) % 26;
        }
    }
    
    return in;
}

}  // namespace rotational_cipher
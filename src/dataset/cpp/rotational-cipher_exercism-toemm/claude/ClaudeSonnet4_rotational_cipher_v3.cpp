#include "rotational_cipher.h"

#include <algorithm>

namespace rotational_cipher {

std::string rotate(std::string in, int shift) {
    const int normalized_shift = ((shift % 26) + 26) % 26;
    
    if (normalized_shift == 0) {
        return in;
    }
    
    std::for_each(in.begin(), in.end(),
                    [normalized_shift] (char& ch) { 
                        if (ch >= 'A' && ch <= 'Z') {
                            ch = 'A' + (ch - 'A' + normalized_shift) % 26;
                        } else if (ch >= 'a' && ch <= 'z') {
                            ch = 'a' + (ch - 'a' + normalized_shift) % 26;
                        }
                    });

    return in;
}

}  // namespace rotational_cipher
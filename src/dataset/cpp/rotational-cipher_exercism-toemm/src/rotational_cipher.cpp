#include "rotational_cipher.h"

#include <algorithm>

namespace rotational_cipher {

std::string rotate(std::string in, int shift) {


    std::for_each(in.begin(), in.end(),
                    [shift] (auto& ch) { 
                        if (isalpha(ch)) {

                            int shift_by = isupper(ch) ? ch - 'A' : ch - 'a';
                            shift_by = (shift_by + shift) % 26;
                            ch = (isupper(ch) ? 'A' : 'a') + shift_by;

                        }
                    });

    return in;

}

}  // namespace rotational_cipher

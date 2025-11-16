#include "rotational_cipher.h"

namespace rotational_cipher {

std::string rotate(std::string in, int shift) {
    shift %= 26; // Reduce unnecessary large shifts
    for (char& ch : in) {
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            ch = base + (ch - base + shift + 26) % 26; // Ensure positive modulo
        }
    }
    return in;
}

}  // namespace rotational_cipher
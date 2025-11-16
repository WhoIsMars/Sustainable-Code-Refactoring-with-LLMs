#include "rotational_cipher.h"

#include <cctype>

namespace rotational_cipher {

std::string rotate(std::string in, int shift) {
    shift %= 26; // Reduce unnecessary computations for large shifts
    for (char& ch : in) {
        if (std::isalpha(ch)) {
            char base = std::isupper(ch) ? 'A' : 'a';
            ch = base + (ch - base + shift + 26) % 26; // Ensure positive modulo
        }
    }
    return in;
}

}  // namespace rotational_cipher
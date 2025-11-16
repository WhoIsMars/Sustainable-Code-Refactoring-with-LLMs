#include "crypto_square.h"

#include <cmath>
#include <algorithm>

namespace crypto_square {

using namespace std;

crypto_square::crypto_square(string msg) : _msg(move(msg)) {}

string crypto_square::normalized_cipher_text() {
    string normalized;
    for (char ch : _msg) {
        if (isalnum(ch)) {
            normalized += tolower(ch);
        }
    }

    size_t length = normalized.size();
    if (length == 0) return "";

    size_t c = ceil(sqrt(length));
    size_t r = (c * (c - 1) >= length) ? c - 1 : c;

    normalized.resize(r * c, ' ');

    string cipher_text;
    cipher_text.reserve(r * c + c - 1);

    for (size_t col = 0; col < c; ++col) {
        for (size_t row = 0; row < r; ++row) {
            char ch = normalized[row * c + col];
            if (ch != ' ') cipher_text += ch;
        }
        cipher_text += ' ';
    }

    if (!cipher_text.empty()) cipher_text.pop_back();

    return cipher_text;
}

crypto_square cipher(string msg) {
    return crypto_square{move(msg)};
}

}  // namespace crypto_square
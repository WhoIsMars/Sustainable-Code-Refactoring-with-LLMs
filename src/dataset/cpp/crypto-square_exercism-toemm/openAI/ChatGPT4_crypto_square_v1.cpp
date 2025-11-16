#include "crypto_square.h"

#include <cmath>
#include <cctype>
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

    int length = normalized.size();
    if (length == 0) return "";

    int c = ceil(sqrt(length));
    int r = (c * (c - 1) >= length) ? c - 1 : c;

    normalized.resize(r * c, ' ');

    string cipher_text;
    cipher_text.reserve(r * c + c - 1); // Reserve space to avoid reallocations

    for (int col = 0; col < c; ++col) {
        if (col > 0) cipher_text += ' ';
        for (int row = 0; row < r; ++row) {
            char ch = normalized[row * c + col];
            if (ch != ' ') cipher_text += ch;
        }
    }

    return cipher_text;
}

crypto_square cipher(string msg) {
    return crypto_square{move(msg)};
}

}  // namespace crypto_square
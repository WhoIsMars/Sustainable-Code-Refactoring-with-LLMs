#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <string>
#include <vector>

namespace crypto_square {

using namespace std;

crypto_square::crypto_square(string msg) : _msg(move(msg)) {}

string crypto_square::normalized_cipher_text() {
    string normalized_msg;
    normalized_msg.reserve(_msg.length()); // Pre-allocate memory

    for (char ch : _msg) {
        if (isalnum(ch)) {
            normalized_msg += tolower(ch);
        }
    }

    size_t length = normalized_msg.length();
    if (length == 0) return "";

    int c = ceil(sqrt(length));
    int r = (length + c - 1) / c; // Equivalent to ceil(length / (double)c) but avoids floating-point division

    string padded_msg = normalized_msg;
    padded_msg.resize(r * c, ' '); // Directly resize and pad with spaces

    string cipher_text;
    cipher_text.reserve(r * c + c - 1); // Pre-allocate memory for cipher text

    for (int j = 0; j < c; ++j) {
        for (int k = 0; k < r; ++k) {
            cipher_text += padded_msg[j + k * c];
        }
        if (j < c - 1) {
            cipher_text += ' ';
        }
    }

    return cipher_text;
}

crypto_square cipher(string msg) { return crypto_square{move(msg)}; }

} // namespace crypto_square
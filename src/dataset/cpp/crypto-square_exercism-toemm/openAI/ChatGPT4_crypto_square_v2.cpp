#include "crypto_square.h"

#include <cmath>
#include <cctype>
#include <string>
#include <vector>

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

    vector<string> rows(r, string(c, ' '));
    for (int i = 0; i < length; ++i) {
        rows[i / c][i % c] = normalized[i];
    }

    string cipher_text;
    for (int col = 0; col < c; ++col) {
        for (int row = 0; row < r; ++row) {
            if (rows[row][col] != ' ') {
                cipher_text += rows[row][col];
            }
        }
        if (col < c - 1) cipher_text += ' ';
    }

    return cipher_text;
}

crypto_square cipher(string msg) {
    return crypto_square{move(msg)};
}

}  // namespace crypto_square
#include "crypto_square.h"

#include <cmath>

namespace crypto_square {

using namespace std;

crypto_square::crypto_square(string msg) : _msg(move(msg)) {}



string crypto_square::normalized_cipher_text() {

    string out, cipher_text;
    int length{}, r{}, c{};
    string word;

    for (auto ch : _msg) {
        if (isalnum(ch)) {
            out += tolower(ch);
            length++;
        }
    }

    if (length == 0) return out;

    while (1) {

        c++;
        if (r * c >= length && c >= r && c - r <= 1) break;

        r++;
        if (r * c >= length && c >= r && c - r <= 1) break;
    }

    // pad out, with empty spaces, 32 == white space
    for (int k{c*r - length}; k > 0; k--) {
        out.push_back(32);
    }


    for (int j{}; j < c; j++) {

        for (int k{}; k < r; k++) {

            auto ch = out[j + k * c];

            // insert whitespace at end if whitespaces is encountered at the end
            if (ch == 32) word.push_back(32);
            else word += ch;
            
        }
        word += " ";
        cipher_text += word;
        word.clear();
    }

    // pop last whitespace added above
    cipher_text.pop_back();



    return cipher_text;
}

crypto_square cipher(string msg) {
    return crypto_square{move(msg)};
}



}  // namespace crypto_square

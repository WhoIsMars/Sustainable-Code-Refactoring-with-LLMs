#include "atbash_cipher.h"
#include <algorithm>
#include <cctype>

std::string atbash_cipher::encode(const std::string &plain) noexcept {
    std::string ciphertext;
    ciphertext.reserve(plain.length() * 2 / 5 + 1); // Pre-allocate space

    int index = 0;
    for (char ch : plain) {
        char c = tolower(ch);
        if (!isalnum(c)) continue;

        if (index > 0 && index % 5 == 0) {
            ciphertext.push_back(' ');
        }

        if (isdigit(c)) {
            ciphertext.push_back(c);
        } else {
            ciphertext.push_back('z' - c + 'a');
        }
        ++index;
    }
    return ciphertext;
}

std::string atbash_cipher::decode(const std::string &cipher) {
    std::string plaintext;
    plaintext.reserve(cipher.length());

    for (char c : cipher) {
        if (c == ' ') continue;

        if (isdigit(c)) {
            plaintext.push_back(c);
        } else if (isalpha(c)) {
            plaintext.push_back('a' - c + 'z');
        } else {
            throw std::domain_error("Bad cipher");
        }
    }
    return plaintext;
}
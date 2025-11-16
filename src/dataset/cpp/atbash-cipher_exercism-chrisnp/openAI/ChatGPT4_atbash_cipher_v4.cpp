#include "atbash_cipher.h"
#include "test/catch.hpp"
#include <cctype>

std::string atbash_cipher::encode(const std::string &plain) noexcept {
    std::string ciphertext;
    ciphertext.reserve(plain.size()); // Reserve memory to avoid reallocations
    int index = 0;

    for (char ch : plain) {
        if (std::isalnum(ch)) {
            if (index > 0 && index % 5 == 0) ciphertext.push_back(' ');
            if (std::isdigit(ch)) {
                ciphertext.push_back(ch);
            } else {
                char c = std::tolower(ch);
                ciphertext.push_back('z' - c + 'a');
            }
            ++index;
        }
    }
    return ciphertext;
}

std::string atbash_cipher::decode(const std::string &cipher) {
    std::string plaintext;
    plaintext.reserve(cipher.size()); // Reserve memory to avoid reallocations

    for (char c : cipher) {
        if (std::isalnum(c)) {
            if (std::isdigit(c)) {
                plaintext.push_back(c);
            } else if (std::isalpha(c)) {
                plaintext.push_back('a' - std::tolower(c) + 'z');
            }
        } else if (!std::isspace(c)) {
            Catch::throw_domain_error("Bad cipher");
        }
    }
    return plaintext;
}
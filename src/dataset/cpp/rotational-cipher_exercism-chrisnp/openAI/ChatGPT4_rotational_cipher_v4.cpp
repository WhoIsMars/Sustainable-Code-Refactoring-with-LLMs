#include "rotational_cipher.h"

std::string 
rotational_cipher::rotate(const std::string &plaintext, int shift) noexcept {
    shift %= ALPHABET;
    std::string enciphered;
    enciphered.reserve(plaintext.size());
    for (char ch : plaintext) {
        if (std::isalpha(ch)) {
            char base = std::islower(ch) ? rotational_cipher::ALPHA_LOWER : rotational_cipher::ALPHA_UPPER;
            enciphered.push_back(base + (ch - base + shift) % ALPHABET);
        } else {
            enciphered.push_back(ch);
        }
    }
    return enciphered;
}
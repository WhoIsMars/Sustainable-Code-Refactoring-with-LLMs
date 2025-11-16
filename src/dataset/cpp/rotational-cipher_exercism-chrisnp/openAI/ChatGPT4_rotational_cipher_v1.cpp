#include "rotational_cipher.h"

std::string 
rotational_cipher::rotate(const std::string &plaintext, int shift) noexcept {
    shift %= ALPHABET;
    std::string enciphered;
    enciphered.reserve(plaintext.size()); // Reserve memory upfront to avoid reallocations

    for (char ch : plaintext) {
        if (std::isalpha(ch)) {
            char alpha = std::islower(ch) ? rotational_cipher::ALPHA_LOWER 
                                          : rotational_cipher::ALPHA_UPPER;
            ch = alpha + (ch - alpha + shift) % ALPHABET;
        }
        enciphered.push_back(ch);
    }
    return enciphered;
}
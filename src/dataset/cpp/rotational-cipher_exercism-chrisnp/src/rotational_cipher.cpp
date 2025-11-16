#include "rotational_cipher.h"

std::string 
rotational_cipher::rotate(const string &plaintext, int shift) noexcept {
    string enciphered {};
    shift %= ALPHABET;
    for (auto ch: plaintext) {
        auto const alpha {std::islower(ch) ? rotational_cipher::ALPHA_LOWER 
                                           : rotational_cipher::ALPHA_UPPER};
        if (std::isalpha(ch)) ch = alpha + (ch - alpha + shift) % ALPHABET;
        enciphered += ch;
    }
    return { enciphered.begin(), enciphered.end() };
}

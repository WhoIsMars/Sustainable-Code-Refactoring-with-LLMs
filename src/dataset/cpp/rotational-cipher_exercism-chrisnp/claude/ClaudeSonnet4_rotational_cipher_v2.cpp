#include "rotational_cipher.h"

std::string 
rotational_cipher::rotate(const string &plaintext, int shift) noexcept {
    string enciphered;
    enciphered.reserve(plaintext.size());
    shift %= ALPHABET;
    
    for (char ch : plaintext) {
        if (std::isalpha(ch)) {
            const char base = std::islower(ch) ? 'a' : 'A';
            ch = base + (ch - base + shift) % ALPHABET;
        }
        enciphered.push_back(ch);
    }
    return enciphered;
}
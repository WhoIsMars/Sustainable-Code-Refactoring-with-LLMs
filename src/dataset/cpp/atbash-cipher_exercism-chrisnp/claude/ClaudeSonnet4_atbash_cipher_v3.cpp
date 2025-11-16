#include "atbash_cipher.h"
#include "test/catch.hpp"

std::string atbash_cipher::encode(const std::string &plain) noexcept {
    std::string ciphertext;
    ciphertext.reserve(plain.length() + plain.length() / 5);
    
    int index = 0;
    for (char ch : plain) {
        if (ch >= 'A' && ch <= 'Z') {
            ch += 32;
        }
        
        if ((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9')) {
            if (index > 0 && index % 5 == 0) {
                ciphertext += ' ';
            }
            
            if (ch >= '0' && ch <= '9') {
                ciphertext += ch;
            } else {
                ciphertext += static_cast<char>('z' - ch + 'a');
            }
            ++index;
        }
    }
    return ciphertext;
}

std::string atbash_cipher::decode(const std::string &cipher) {
    std::string plaintext;
    plaintext.reserve(cipher.length());
    
    for (char c : cipher) {
        if (c == ' ') continue;
        
        if (c >= '0' && c <= '9') {
            plaintext += c;
        } else if (c >= 'a' && c <= 'z') {
            plaintext += static_cast<char>('a' - c + 'z');
        } else {
            Catch::throw_domain_error("Bad cipher");
        }
    }
    return plaintext;
}
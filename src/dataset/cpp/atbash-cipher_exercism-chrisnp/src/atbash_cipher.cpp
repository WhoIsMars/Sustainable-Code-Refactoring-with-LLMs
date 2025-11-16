#include "atbash_cipher.h"
#include "test/catch.hpp"

std::string atbash_cipher::encode(const std::string &plain) noexcept {
    std::string ciphertext {};
    int index {0};
    for( auto &ch: plain) {
        char c = tolower(ch);
        if( !(atbash_cipher::alpha(c) || atbash_cipher::digit(c)) ) continue; 
        if( index > 0 && index % 5 == 0) ciphertext.push_back(' ');
        if( atbash_cipher::digit(c) ) ciphertext.push_back(c);
        if( atbash_cipher::alpha(c) ) ciphertext.push_back('z' - c + 'a');
        ++index;
    }
    return ciphertext;
}

std::string atbash_cipher::decode(const std::string &cipher) {
    std::string plaintext {};
    for( auto &c: cipher ) {
        if( c == ' ') continue;
        if( atbash_cipher::digit(c) ) plaintext.push_back(c);
        if( atbash_cipher::alpha(c) ) plaintext.push_back('a' - c + 'z');
        if( !atbash_cipher::alpha(c) && !atbash_cipher::digit(c) )
            Catch::throw_domain_error("Bad cipher");
    }
    return plaintext;
}

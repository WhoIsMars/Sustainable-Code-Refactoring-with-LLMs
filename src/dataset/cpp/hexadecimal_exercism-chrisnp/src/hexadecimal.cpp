#include "hexadecimal.h"

uint64_t hexadecimal::convert(const string &hex_string) noexcept {
    
    int hex {0};

    for (auto ch : hex_string) {
        hex <<= 4;
        if (isdigit(ch)) 
            hex |= ch - '0';
        else if (islower(ch) && ch <= 'f')
            hex |= ch - 'a' + 10;
        else if (isupper(ch) && ch <= 'F')
            hex |= ch - 'A' + 10;
        else 
            hex = 0;
    }

    return hex;
}

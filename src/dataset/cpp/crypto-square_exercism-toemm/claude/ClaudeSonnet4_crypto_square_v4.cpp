#include "crypto_square.h"

#include <cmath>

namespace crypto_square {

using namespace std;

crypto_square::crypto_square(string msg) : _msg(move(msg)) {}

string crypto_square::normalized_cipher_text() {
    string normalized;
    normalized.reserve(_msg.size());
    
    for (char ch : _msg) {
        if (isalnum(ch)) {
            normalized += static_cast<char>(tolower(ch));
        }
    }
    
    const int length = normalized.size();
    if (length == 0) return normalized;
    
    const int c = static_cast<int>(ceil(sqrt(length)));
    const int r = (length + c - 1) / c;
    
    normalized.resize(r * c, ' ');
    
    string result;
    result.reserve(length + c);
    
    for (int j = 0; j < c; j++) {
        if (j > 0) result += ' ';
        
        for (int k = 0; k < r; k++) {
            char ch = normalized[k * c + j];
            if (ch != ' ') {
                result += ch;
            }
        }
    }
    
    return result;
}

crypto_square cipher(string msg) {
    return crypto_square{move(msg)};
}

}  // namespace crypto_square
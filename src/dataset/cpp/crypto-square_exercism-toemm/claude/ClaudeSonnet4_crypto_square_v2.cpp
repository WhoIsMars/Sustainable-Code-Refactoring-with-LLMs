#include "crypto_square.h"

#include <cmath>

namespace crypto_square {

using namespace std;

crypto_square::crypto_square(string msg) : _msg(move(msg)) {}

string crypto_square::normalized_cipher_text() {
    // Pre-filter and normalize in single pass
    string normalized;
    normalized.reserve(_msg.size()); // Reserve space to avoid reallocations
    
    for (char ch : _msg) {
        if (isalnum(ch)) {
            normalized += tolower(ch);
        }
    }
    
    int length = normalized.size();
    if (length == 0) return normalized;

    // Calculate dimensions more efficiently
    int c = static_cast<int>(ceil(sqrt(length)));
    int r = (length + c - 1) / c; // Ceiling division
    
    // Ensure c >= r and c - r <= 1
    if (c < r) {
        c = r;
    }

    // Build result directly without intermediate padding
    string result;
    result.reserve(length + c); // Approximate final size
    
    for (int j = 0; j < c; j++) {
        if (j > 0) result += ' ';
        
        for (int k = 0; k < r; k++) {
            int idx = j + k * c;
            if (idx < length) {
                result += normalized[idx];
            }
        }
    }

    return result;
}

crypto_square cipher(string msg) {
    return crypto_square{move(msg)};
}

}  // namespace crypto_square
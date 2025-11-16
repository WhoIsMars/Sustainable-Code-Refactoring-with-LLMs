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
            normalized += static_cast<char>(tolower(ch));
        }
    }
    
    const int length = normalized.size();
    if (length == 0) return normalized;
    
    // Calculate dimensions more efficiently
    const int c = static_cast<int>(ceil(sqrt(length)));
    const int r = (length + c - 1) / c; // Ceiling division
    
    // Pad normalized string directly
    normalized.resize(r * c, ' ');
    
    // Build result string with pre-calculated size
    string result;
    result.reserve(length + c - 1); // length + spaces between columns
    
    for (int j = 0; j < c; j++) {
        if (j > 0) result += ' ';
        
        for (int k = 0; k < r; k++) {
            char ch = normalized[j + k * c];
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
#include "run_length_encoding.h"

using std::string;
using std::to_string;

string run_length_encoding::encode(const string &decoded) noexcept {
    if (decoded.empty()) return {};
    
    string encoded;
    encoded.reserve(decoded.size());
    
    int count = 1;
    char cur = decoded[0];
    
    for (size_t i = 1; i < decoded.size(); ++i) {
        if (decoded[i] == cur) {
            ++count;
        } else {
            if (count > 1) {
                encoded += to_string(count);
            }
            encoded += cur;
            cur = decoded[i];
            count = 1;
        }
    }
    
    if (count > 1) {
        encoded += to_string(count);
    }
    encoded += cur;
    
    return encoded;
}

string run_length_encoding::decode(const string &encoded) noexcept {
    if (encoded.empty()) return {};
    
    string decoded;
    decoded.reserve(encoded.size() * 2);
    
    int count = 0;
    for (char ch : encoded) {
        if (ch >= '0' && ch <= '9') {
            count = count * 10 + (ch - '0');
        } else {
            if (count == 0) count = 1;
            decoded.append(count, ch);
            count = 0;
        }
    }
    
    return decoded;
}
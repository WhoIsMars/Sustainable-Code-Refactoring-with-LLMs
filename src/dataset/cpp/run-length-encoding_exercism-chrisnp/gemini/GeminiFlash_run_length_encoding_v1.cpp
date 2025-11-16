#include "run_length_encoding.h"

#include <cctype>
#include <string>
#include <algorithm>

using std::string;

string run_length_encoding::encode(const string &decoded) noexcept {
    if (decoded.empty()) return {};

    string encoded;
    encoded.reserve(decoded.length()); // Pre-allocate memory

    char current_char = decoded[0];
    int count = 1;

    for (size_t i = 1; i < decoded.length(); ++i) {
        if (decoded[i] == current_char) {
            count++;
        } else {
            if (count > 1) {
                encoded += std::to_string(count);
            }
            encoded += current_char;
            current_char = decoded[i];
            count = 1;
        }
    }

    if (count > 1) {
        encoded += std::to_string(count);
    }
    encoded += current_char;

    return encoded;
}

string run_length_encoding::decode(const string &encoded) noexcept {
    if (encoded.empty()) return {};

    string decoded;
    decoded.reserve(encoded.length()); // Pre-allocate memory

    int count = 0;
    for (char ch : encoded) {
        if (isdigit(ch)) {
            count = count * 10 + (ch - '0');
        } else {
            if (count == 0) {
                decoded += ch;
            } else {
                decoded.append(count, ch);
                count = 0;
            }
        }
    }
    return decoded;
}
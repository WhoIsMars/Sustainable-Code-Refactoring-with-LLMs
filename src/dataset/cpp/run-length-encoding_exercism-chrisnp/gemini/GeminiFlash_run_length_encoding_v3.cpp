#include "run_length_encoding.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

using std::string;
using std::to_string;

string run_length_encoding::encode(const string &decoded) noexcept {
    if (decoded.empty()) return {};

    string encoded;
    encoded.reserve(decoded.length()); 

    char current_char = decoded[0];
    int count = 1;

    for (size_t i = 1; i < decoded.length(); ++i) {
        if (decoded[i] == current_char) {
            ++count;
        } else {
            if (count > 1) {
                encoded += to_string(count);
            }
            encoded.push_back(current_char);
            current_char = decoded[i];
            count = 1;
        }
    }

    if (count > 1) {
        encoded += to_string(count);
    }
    encoded.push_back(current_char);

    return encoded;
}

string run_length_encoding::decode(const string &encoded) noexcept {
    if (encoded.empty()) return {};

    string decoded;
    decoded.reserve(encoded.length());

    int count = 0;
    for (char ch : encoded) {
        if (isdigit(ch)) {
            count = count * 10 + (ch - '0');
        } else {
            if (count == 0) {
                decoded.push_back(ch);
            } else {
                decoded.append(count, ch);
                count = 0;
            }
        }
    }
    return decoded;
}
#include "run_length_encoding.h"

using std::string;
using std::to_string;

string run_length_encoding::encode(const string &decoded) noexcept {
    if (decoded.empty()) return {};
    string encoded;
    encoded.reserve(decoded.size()); // Reserve memory to minimize reallocations
    char cur = decoded[0];
    int count = 1;

    for (size_t i = 1; i < decoded.size(); ++i) {
        if (decoded[i] == cur) {
            ++count;
        } else {
            if (count > 1) encoded += to_string(count);
            encoded.push_back(cur);
            cur = decoded[i];
            count = 1;
        }
    }
    if (count > 1) encoded += to_string(count);
    encoded.push_back(cur);
    return encoded;
}

string run_length_encoding::decode(const string &encoded) noexcept {
    if (encoded.empty()) return {};
    string decoded;
    decoded.reserve(encoded.size()); // Reserve memory to minimize reallocations
    int count = 0;

    for (char ch : encoded) {
        if (isdigit(ch)) {
            count = 10 * count + (ch - '0');
        } else {
            count = (count == 0) ? 1 : count;
            decoded.append(count, ch); // Use append for better performance
            count = 0;
        }
    }
    return decoded;
}
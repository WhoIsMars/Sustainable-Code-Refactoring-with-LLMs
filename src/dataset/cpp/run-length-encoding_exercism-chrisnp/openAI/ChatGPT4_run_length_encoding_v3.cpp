#include "run_length_encoding.h"

using std::string;
using std::to_string;

string run_length_encoding::encode(const string &decoded) noexcept {
    if (decoded.empty()) return {};
    string encoded;
    encoded.reserve(decoded.size());
    char cur = decoded[0];
    int count = 1;

    for (size_t i = 1; i < decoded.size(); ++i) {
        if (decoded[i] == cur) {
            ++count;
        } else {
            if (count > 1) encoded += to_string(count);
            encoded += cur;
            cur = decoded[i];
            count = 1;
        }
    }
    if (count > 1) encoded += to_string(count);
    encoded += cur;
    return encoded;
}

string run_length_encoding::decode(const string &encoded) noexcept {
    if (encoded.empty()) return {};
    string decoded;
    decoded.reserve(encoded.size());
    int count = 0;

    for (char ch : encoded) {
        if (isdigit(ch)) {
            count = count * 10 + (ch - '0');
        } else {
            count = count == 0 ? 1 : count;
            decoded.append(count, ch);
            count = 0;
        }
    }
    return decoded;
}
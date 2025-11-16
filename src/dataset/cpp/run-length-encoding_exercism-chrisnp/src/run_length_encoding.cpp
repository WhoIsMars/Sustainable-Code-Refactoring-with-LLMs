#include "run_length_encoding.h"

using std::string;
using std::to_string;

string run_length_encoding::encode(const string &decoded) noexcept {
    auto encoded = string {};
    if (decoded.empty()) return encoded;
    auto count = int {0};
    auto cur = char {decoded.at(0)};
    for (auto ch : decoded) {
        if (ch == cur) count++;
        else {
            if (count > 1) encoded += to_string(count);
            encoded.push_back(cur);
            cur = ch;
            count = 1;
        }
    }
    if (count > 1) encoded += to_string(count);
    encoded.push_back(cur);
    return encoded;
}

string run_length_encoding::decode(const string &encoded) noexcept {
    auto decoded = string {};
    if (encoded.empty()) return decoded;
    auto count = int {0};
    for (auto ch : encoded) {
        if (isdigit(ch)) count = 10 * count + ch - '0';
        else {
            if (count == 0) count = 1;
            for (auto i = int{0}; i < count; ++i) decoded += ch;
            count = 0;
        }
    } 
    return decoded;
}

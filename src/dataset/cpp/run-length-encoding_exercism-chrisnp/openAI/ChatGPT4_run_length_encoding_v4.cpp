#include "run_length_encoding.h"
#include <sstream>

using std::string;
using std::to_string;

string run_length_encoding::encode(const string &decoded) noexcept {
    if (decoded.empty()) return {};
    std::ostringstream encoded;
    char cur = decoded[0];
    int count = 0;

    for (char ch : decoded) {
        if (ch == cur) {
            ++count;
        } else {
            if (count > 1) encoded << count;
            encoded.put(cur);
            cur = ch;
            count = 1;
        }
    }
    if (count > 1) encoded << count;
    encoded.put(cur);

    return encoded.str();
}

string run_length_encoding::decode(const string &encoded) noexcept {
    if (encoded.empty()) return {};
    std::ostringstream decoded;
    int count = 0;

    for (char ch : encoded) {
        if (isdigit(ch)) {
            count = count * 10 + (ch - '0');
        } else {
            count = count == 0 ? 1 : count;
            decoded << string(count, ch);
            count = 0;
        }
    }

    return decoded.str();
}
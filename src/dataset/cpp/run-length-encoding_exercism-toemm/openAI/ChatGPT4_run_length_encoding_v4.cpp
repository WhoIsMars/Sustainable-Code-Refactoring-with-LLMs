#include "run_length_encoding.h"
#include <sstream>

namespace run_length_encoding {

std::string encode(const std::string& in) noexcept {
    if (in.empty()) return "";

    std::ostringstream out;
    int ctr = 1;
    char last_char = in[0];

    for (std::size_t i = 1; i < in.size(); ++i) {
        if (in[i] == last_char) {
            ++ctr;
        } else {
            if (ctr > 1) out << ctr;
            out << last_char;
            last_char = in[i];
            ctr = 1;
        }
    }

    if (ctr > 1) out << ctr;
    out << last_char;

    return out.str();
}

std::string decode(const std::string& in) noexcept {
    if (in.empty()) return "";

    std::ostringstream out;
    int count = 0;

    for (char ch : in) {
        if (std::isdigit(ch)) {
            count = count * 10 + (ch - '0');
        } else {
            out << std::string(count > 0 ? count : 1, ch);
            count = 0;
        }
    }

    return out.str();
}

}  // namespace run_length_encoding
#include "run_length_encoding.h"
#include <algorithm>
#include <cctype>
#include <sstream>

namespace run_length_encoding {

std::string encode(const std::string& in) noexcept {
    if (in.empty()) {
        return "";
    }

    std::string out;
    char last_char = in[0];
    int ctr = 1;

    for (std::size_t i = 1; i < in.size(); ++i) {
        if (in[i] == last_char) {
            ctr++;
        } else {
            if (ctr > 1) {
                out += std::to_string(ctr);
            }
            out += last_char;
            last_char = in[i];
            ctr = 1;
        }
    }

    if (ctr > 1) {
        out += std::to_string(ctr);
    }
    out += last_char;

    return out;
}

std::string decode(const std::string& in) noexcept {
    std::string out;
    std::string digit_str;

    for (char ch : in) {
        if (isdigit(ch)) {
            digit_str += ch;
        } else {
            if (!digit_str.empty()) {
                int count = std::stoi(digit_str);
                out.append(count, ch);
                digit_str.clear();
            } else {
                out += ch;
            }
        }
    }

    return out;
}

}  // namespace run_length_encoding
#include "run_length_encoding.h"

namespace run_length_encoding {

std::string encode(const std::string& in) noexcept {
    if (in.empty()) return "";

    std::string out;
    int ctr = 1;

    for (std::size_t i = 1; i <= in.size(); ++i) {
        if (i < in.size() && in[i] == in[i - 1]) {
            ++ctr;
        } else {
            if (ctr > 1) out += std::to_string(ctr);
            out.push_back(in[i - 1]);
            ctr = 1;
        }
    }

    return out;
}

std::string decode(const std::string& in) noexcept {
    std::string out;
    int count = 0;

    for (char ch : in) {
        if (std::isdigit(ch)) {
            count = count * 10 + (ch - '0');
        } else {
            if (count == 0) {
                out.push_back(ch);
            } else {
                out.append(count, ch);
                count = 0;
            }
        }
    }

    return out;
}

}  // namespace run_length_encoding
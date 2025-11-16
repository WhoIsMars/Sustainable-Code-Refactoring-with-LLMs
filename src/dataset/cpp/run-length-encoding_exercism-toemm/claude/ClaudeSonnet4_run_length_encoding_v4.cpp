#include "run_length_encoding.h"

namespace run_length_encoding {

std::string encode(const std::string& in) noexcept {
    if (in.empty()) return {};
    
    std::string out;
    out.reserve(in.size());
    
    char current_char = in[0];
    int count = 1;
    
    for (std::size_t i = 1; i < in.size(); ++i) {
        if (in[i] == current_char) {
            ++count;
        } else {
            if (count > 1) {
                out += std::to_string(count);
            }
            out += current_char;
            current_char = in[i];
            count = 1;
        }
    }
    
    if (count > 1) {
        out += std::to_string(count);
    }
    out += current_char;
    
    return out;
}

std::string decode(const std::string& in) noexcept {
    if (in.empty()) return {};
    
    std::string out;
    out.reserve(in.size() * 2);
    
    int count = 0;
    
    for (char ch : in) {
        if (ch >= '0' && ch <= '9') {
            count = count * 10 + (ch - '0');
        } else {
            if (count > 0) {
                out.append(count, ch);
                count = 0;
            } else {
                out += ch;
            }
        }
    }
    
    return out;
}

}  // namespace run_length_encoding
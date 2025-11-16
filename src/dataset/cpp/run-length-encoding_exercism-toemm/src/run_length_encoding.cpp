#include "run_length_encoding.h"

namespace run_length_encoding {


std::string encode(const std::string& in) noexcept {

    std::string out;
    int ctr{1};
    char last_char{'\0'};

    for (std::size_t i{}; i < in.size(); i++) {

        auto ch = in[i];

        if (ch == last_char) {
            ctr++;

        // new char
        } else if (ch != last_char && last_char != '\0') {
            
            if (ctr > 1) out += std::to_string(ctr) + last_char;
            else out.push_back(last_char);

            ctr = 1;

            if (i != in.size() -1) last_char = ch;

        // first char
        } else {
            last_char = ch;

        }

        // check last in string
        if (i == in.size() - 1) {
            if (ch == last_char) {
                out += std::to_string(ctr) + ch;
            } else {
                out.push_back(ch);
            }

            continue;
        }


    }


    return out;
    
}

std::string decode(const std::string& in) noexcept {

    std::string out;
    std::string digit{};


    for (std::size_t i{}; i < in.size(); i++) {

        auto ch = in[i];

        if (isdigit(ch)) {

            digit.push_back(ch);
            continue;

        } else {

            if (!digit.empty()) {
                out.append(static_cast<std::size_t>(std::stoi(digit)), ch);
                digit.clear();
                continue;
            }

            out.push_back(ch);
        }



    }

    return out;


}



}  // namespace run_length_encoding

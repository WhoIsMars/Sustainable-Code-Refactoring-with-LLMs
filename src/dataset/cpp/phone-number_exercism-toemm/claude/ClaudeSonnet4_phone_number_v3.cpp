#include "phone_number.h"

#include <stdexcept>
#include <algorithm>

namespace phone_number {

std::string number_class::number() {
    return _number;
}

number_class::number_class(const std::string& number) : _number(number) {
    format_number();
}

void number_class::format_number() {
    std::string out;
    out.reserve(10);

    bool skip_leading_one = false;
    int digit_count = 0;

    for (char c : _number) {
        if (std::isdigit(c)) {
            if (c == '1' && digit_count == 0 && !skip_leading_one) {
                skip_leading_one = true;
                continue;
            }

            if (digit_count == 0 || digit_count == 3) {
                if (c < '2') {
                    throw std::domain_error("invalid area code.");
                }
            }

            out += c;
            ++digit_count;
        }
    }
    
    if (digit_count != 10) {
        throw std::domain_error("Not 10 digits.");
    }

    _number = std::move(out);
}

number_class phone_number(const std::string& number) {
    return number_class(number);
}

}
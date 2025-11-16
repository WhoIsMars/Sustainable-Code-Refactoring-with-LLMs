#include "phone_number.h"

#include <stdexcept>
#include <iostream>

namespace phone_number {

const std::string& number_class::number() const {
    return _number;
}

number_class::number_class(const std::string& number) {
    format_number(number);
}

void number_class::format_number(const std::string& input) {
    _number.clear();
    _number.reserve(10);

    bool skip_first_one = false;
    int digit_count = 0;

    for (char c : input) {
        if (c >= '0' && c <= '9') {
            if (c == '1' && digit_count == 0 && !skip_first_one) {
                skip_first_one = true;
                continue;
            }

            if (digit_count == 0 || digit_count == 3) {
                if (c < '2') {
                    throw std::domain_error("invalid area code.");
                }
            }

            _number += c;
            ++digit_count;
        }
    }
    
    if (digit_count != 10) {
        throw std::domain_error("Not 10 digits.");
    }
}

number_class phone_number(const std::string& number) {
    return number_class(number);
}

}
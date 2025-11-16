#include "phone_number.h"

#include <stdexcept>
#include <iostream>
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

    for (char c : _number) {
        if (isdigit(c)) {
            if (out.size() == 0 && c == '1') {
                continue;
            }
            out += c;
        }
    }

    if (out.size() != 10) {
        throw std::domain_error("Not 10 digits.");
    }

    if (out[0] < '2' || out[3] < '2') {
        throw std::domain_error("invalid area code.");
    }

    _number = out;
}

number_class phone_number(const std::string& number) {
    return number_class(number);
}

}  // namespace phone_number
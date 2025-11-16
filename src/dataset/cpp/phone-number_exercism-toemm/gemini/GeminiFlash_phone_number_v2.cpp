#include "phone_number.h"

#include <stdexcept>
#include <iostream>
#include <algorithm>

namespace phone_number {

number_class::number_class(std::string number) : _number(std::move(number)) {
    format_number();
}

std::string number_class::number() const {
    return _number;
}


void number_class::format_number() {
    std::string out;
    out.reserve(10);

    for (char c : _number) {
        if (isdigit(c)) {
            out += c;
        }
    }

    if (out.size() < 10) {
        throw std::domain_error("Not enough digits.");
    }

    if (out.size() > 10) {
        size_t start_index = out.size() - 10;
        if (out.size() > 11 || out[start_index -1] != '1') {
            out = out.substr(start_index, 10);
        } else {
            out = out.substr(start_index, 10);
        }
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
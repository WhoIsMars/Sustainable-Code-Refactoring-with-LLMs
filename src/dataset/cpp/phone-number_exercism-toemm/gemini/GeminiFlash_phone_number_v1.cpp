#include "phone_number.h"

#include <stdexcept>
#include <cctype>
#include <algorithm>

namespace phone_number {

number_class::number_class(std::string number) : _number(std::move(number)) {
    format_number();
}

std::string number_class::number() const {
    return _number;
}

void number_class::format_number() {
    std::string digits_only;
    digits_only.reserve(_number.size()); // Reserve space to avoid reallocations

    for (char c : _number) {
        if (isdigit(c)) {
            digits_only += c;
        }
    }

    if (digits_only.size() == 11 && digits_only[0] == '1') {
        digits_only.erase(0, 1);
    }

    if (digits_only.size() != 10) {
        throw std::domain_error("Must be 10 or 11 digits (if 11, must start with 1)");
    }

    if (digits_only[0] < '2' || digits_only[3] < '2') {
        throw std::domain_error("Area code and exchange code must start with 2-9");
    }

    _number = digits_only;
}

number_class phone_number(const std::string& number) {
    return number_class(number);
}

}  // namespace phone_number
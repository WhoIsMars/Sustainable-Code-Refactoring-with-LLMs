#include "phone_number.h"

#include <stdexcept>
#include <cctype>

namespace phone_number {

std::string number_class::number() const {
    return _number;
}

number_class::number_class(const std::string& number) {
    _number = format_number(number);
}

std::string number_class::format_number(const std::string& number) {
    std::string out;
    int digit_count = 0;

    for (char ch : number) {
        if (std::isdigit(ch)) {
            if (digit_count == 0 && ch == '1') {
                continue; // Skip leading '1'
            }

            if ((digit_count == 0 || digit_count == 3) && ch < '2') {
                throw std::domain_error("Invalid area code.");
            }

            out += ch;
            if (++digit_count > 10) {
                throw std::domain_error("Not 10 digits.");
            }
        }
    }

    if (digit_count != 10) {
        throw std::domain_error("Not 10 digits.");
    }

    return out;
}

number_class phone_number(const std::string& number) {
    return number_class(number);
}

}  // namespace phone_number
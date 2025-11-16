#include "phone_number.h"

#include <stdexcept>
#include <cctype>
#include <string>

namespace phone_number {

std::string number_class::number() {
    return _number;
}

number_class::number_class(const std::string& number) : _number(number) {
    format_number();
}

void number_class::format_number() {
    std::string out;
    out.reserve(10); // Reserve space for 10 digits to avoid reallocations

    int ctr = 0;

    for (char ch : _number) {
        if (std::isdigit(ch)) {
            if (out.empty() && ch == '1') {
                continue; // Skip leading '1'
            }

            if ((ctr == 0 || ctr == 3) && ch < '2') {
                throw std::domain_error("invalid area code.");
            }

            out += ch;
            if (++ctr == 10) break; // Stop processing once 10 digits are collected
        }
    }

    if (ctr != 10) throw std::domain_error("Not 10 digits.");

    _number = std::move(out);
}

number_class phone_number(const std::string& number) {
    return number_class(number);
}

} // namespace phone_number
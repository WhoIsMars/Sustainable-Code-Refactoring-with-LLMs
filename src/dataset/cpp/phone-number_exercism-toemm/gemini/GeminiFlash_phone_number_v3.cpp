#include "phone_number.h"

#include <stdexcept>
#include <iostream>
#include <algorithm>

namespace phone_number {

std::string number_class::number() const {
    return _number;
}

number_class::number_class(std::string number) : _number(std::move(number)) {
    format_number();
}

void number_class::format_number() {
    std::string out;
    out.reserve(10);

    int ctr = 0;
    bool leading_one_removed = false;

    for (char c : _number) {
        if (isdigit(c)) {
            if (c == '1' && out.empty() && !leading_one_removed) {
                leading_one_removed = true;
                continue;
            }

            ctr++;

            if (ctr == 1 || ctr == 4) {
                if (c < '2')
                    throw std::domain_error("invalid area code.");
            }

            out += c;
        }
    }

    if (out.size() != 10) throw std::domain_error("Not 10 digits.");

    _number = std::move(out);
}

number_class phone_number(const std::string& number) {
    return number_class(number);
}

}  // namespace phone_number
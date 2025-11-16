#include "phone_number.h"

#include <stdexcept>
#include <iostream>

namespace phone_number {


std::string number_class::number() {
    return _number;
}

number_class::number_class(const std::string& number) : _number(std::move(number)) {
    format_number();
}

void number_class::format_number() {
    std::string out{};

    int ctr{};
    bool flag = false;

    for (std::size_t i = 0; i < _number.size(); i++) {

        if (isdigit(_number[i])) {

            // check first digit can be 1
            if (_number[i] == '1' && out.empty() && flag == false) {
                flag = true;
                continue;  
            }

            ctr++;

            // area code check 
            if (ctr == 1 || ctr == 4) {
                if (_number[i] < '2')
                    throw std::domain_error("invalid area code.");
            }

            out += _number[i];

        }
    }
    
    if (out.size() != 10) throw std::domain_error("Not 10 digits.");

    _number = out;
}

number_class phone_number(const std::string& number) {
    return number_class(number);
}

}



  // namespace phone_number

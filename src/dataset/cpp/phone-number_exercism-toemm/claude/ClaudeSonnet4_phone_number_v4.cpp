#include "phone_number.h"

#include <stdexcept>

namespace phone_number {

std::string number_class::number() {
    return _number;
}

number_class::number_class(const std::string& number) {
    _number.reserve(10);
    format_number(number);
}

void number_class::format_number(const std::string& input) {
    _number.clear();
    
    bool skip_first_one = false;
    const char* ptr = input.data();
    const char* end = ptr + input.size();
    
    while (ptr < end) {
        const char c = *ptr++;
        
        if (c >= '0' && c <= '9') {
            if (c == '1' && _number.empty() && !skip_first_one) {
                skip_first_one = true;
                continue;
            }
            
            const std::size_t pos = _number.size();
            if ((pos == 0 || pos == 3) && c < '2') {
                throw std::domain_error("invalid area code.");
            }
            
            _number += c;
        }
    }
    
    if (_number.size() != 10) {
        throw std::domain_error("Not 10 digits.");
    }
}

number_class phone_number(const std::string& number) {
    return number_class(number);
}

}
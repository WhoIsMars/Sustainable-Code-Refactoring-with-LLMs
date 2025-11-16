#include "luhn.h"

namespace luhn {

bool valid(std::string test) {
    int sum = 0;
    int digit_count = 0;
    bool double_next = false;
    
    for (auto it = test.rbegin(); it != test.rend(); ++it) {
        const char ch = *it;
        
        if (ch == ' ') continue;
        
        if (ch < '0' || ch > '9') return false;
        
        int digit = ch - '0';
        
        if (double_next) {
            digit <<= 1;
            if (digit > 9) digit -= 9;
        }
        
        sum += digit;
        ++digit_count;
        double_next = !double_next;
    }
    
    return digit_count > 1 && sum % 10 == 0;
}

}  // namespace luhn
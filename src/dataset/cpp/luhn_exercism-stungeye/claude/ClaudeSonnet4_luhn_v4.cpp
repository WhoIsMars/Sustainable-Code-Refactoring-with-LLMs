#include "luhn.h"

namespace luhn {
    bool valid(std::string_view number) {
        int sum = 0;
        int digit_count = 0;
        bool alternate = false;
        
        for (auto it = number.rbegin(); it != number.rend(); ++it) {
            const char c = *it;
            
            if (c == ' ') continue;
            
            const int digit = c - '0';
            if (digit < 0 || digit > 9) return false;
            
            ++digit_count;
            
            if (alternate) {
                const int doubled = digit << 1;
                sum += (doubled > 9) ? doubled - 9 : doubled;
            } else {
                sum += digit;
            }
            
            alternate = !alternate;
        }
        
        return digit_count > 1 && sum % 10 == 0;
    }
} // namespace luhn
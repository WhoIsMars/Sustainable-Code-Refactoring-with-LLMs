#include "luhn.h"

namespace luhn {
    bool valid(std::string_view number) {
        if (number.length() <= 1) return false;
        
        int sum = 0;
        int digitCount = 0;
        bool isEven = false;
        
        for (auto it = number.rbegin(); it != number.rend(); ++it) {
            const char c = *it;
            
            if (c == ' ') continue;
            
            const int digit = c - '0';
            if (digit < 0 || digit > 9) return false;
            
            ++digitCount;
            
            if (isEven) {
                const int doubled = digit << 1;
                sum += (doubled > 9) ? doubled - 9 : doubled;
            } else {
                sum += digit;
            }
            
            isEven = !isEven;
        }
        
        return digitCount > 1 && sum % 10 == 0;
    }
} // namespace luhn
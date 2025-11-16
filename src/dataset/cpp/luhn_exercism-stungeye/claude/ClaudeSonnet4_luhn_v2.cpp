#include "luhn.h"

namespace luhn {
    bool valid(std::string_view number) {
        int sum = 0;
        int digit_count = 0;
        bool alternate = false;
        
        // Process from right to left without storing digits
        for (auto it = number.rbegin(); it != number.rend(); ++it) {
            const char c = *it;
            
            if (c == ' ') continue;
            
            const int n = c - '0';
            if (n < 0 || n > 9) return false;
            
            ++digit_count;
            
            if (alternate) {
                const int doubled = n << 1; // n * 2
                sum += doubled > 9 ? doubled - 9 : doubled;
            } else {
                sum += n;
            }
            
            alternate = !alternate;
        }
        
        return digit_count > 1 && sum % 10 == 0;
    }
} // namespace luhn
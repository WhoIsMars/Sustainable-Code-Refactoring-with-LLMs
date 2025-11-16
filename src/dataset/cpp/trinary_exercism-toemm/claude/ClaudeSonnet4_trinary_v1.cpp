#include "trinary.h"

#include <string>

namespace trinary {

    int to_decimal(const std::string& num) {
        if (num.empty()) return 0;
        
        int out = 0;
        int power = 1;
        
        for (int i = num.size() - 1; i >= 0; --i) {
            int digit = num[i] - '0';
            
            if (digit < 0 || digit > 2) return 0;
            
            out += digit * power;
            power *= 3;
        }
        
        return out;
    }

}  // namespace trinary
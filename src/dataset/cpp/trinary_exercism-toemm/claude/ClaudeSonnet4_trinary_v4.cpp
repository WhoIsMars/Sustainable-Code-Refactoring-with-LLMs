#include "trinary.h"

#include <string>

namespace trinary {

    int to_decimal(const std::string& num) {
        if (num.empty()) return 0;
        
        int out = 0;
        int power = 1;
        
        for (int i = num.size() - 1; i >= 0; --i) {
            const char digit = num[i];
            
            if (digit < '0' || digit > '2') return 0;
            
            out += (digit - '0') * power;
            power *= 3;
        }
        
        return out;
    }

}  // namespace trinary
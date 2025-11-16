#include "binary.h"

using std::string;

long binary::convert (const string& binstr) noexcept {
    long decimal = 0;
    long power = 1;
    
    for (auto it = binstr.rbegin(); it != binstr.rend(); ++it) {
        const char digit = *it;
        if (digit != '0' && digit != '1') return 0;
        
        if (digit == '1') {
            decimal += power;
        }
        power <<= 1;
    }
    
    return decimal;
}
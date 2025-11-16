#include "binary.h"

using std::string;

long binary::convert (const string& binstr) noexcept {
    long decimal = 0;
    long power = 1;
    
    for (auto it = binstr.rbegin(); it != binstr.rend(); ++it) {
        if (*it != '0' && *it != '1') return 0;
        if (*it == '1') {
            decimal += power;
        }
        power <<= 1;
    }
    
    return decimal;
}
#include "binary.h"

using std::string;

long binary::convert (const string& binstr) noexcept {
    long decimal = 0;
    long power = 1;
    
    for (int i = binstr.length() - 1; i >= 0; --i) {
        char c = binstr[i];
        if (c != '0' && c != '1') return 0;
        
        if (c == '1') {
            decimal += power;
        }
        power <<= 1;
    }
    
    return decimal;
}
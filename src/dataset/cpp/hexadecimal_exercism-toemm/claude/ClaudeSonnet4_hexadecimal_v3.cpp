#include "hexadecimal.h"

namespace hexadecimal {

int convert(std::string hex_string) {
    int sum = 0;
    int power = 1;
    
    for (int i = hex_string.length() - 1; i >= 0; --i) {
        char ch = hex_string[i];
        int digit;
        
        if (ch >= '0' && ch <= '9') {
            digit = ch - '0';
        } else if (ch >= 'a' && ch <= 'f') {
            digit = ch - 'a' + 10;
        } else {
            return 0;
        }
        
        sum += digit * power;
        power <<= 4;
    }
    
    return sum;
}

}  // namespace hexadecimal
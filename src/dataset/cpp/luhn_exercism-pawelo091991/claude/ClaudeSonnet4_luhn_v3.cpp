#include "luhn.h"
#include <string>
#include <algorithm>

using std::string;

bool luhn::valid(string str) {
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    
    const size_t len = str.length();
    if (len <= 1) return false;
    
    int sum = 0;
    bool alternate = false;
    
    for (size_t i = len; i > 0; --i) {
        const char c = str[i - 1];
        if (c < '0' || c > '9') return false;
        
        int digit = c - '0';
        
        if (alternate) {
            digit <<= 1;
            if (digit > 9) digit -= 9;
        }
        
        sum += digit;
        alternate = !alternate;
    }
    
    return sum % 10 == 0;
}
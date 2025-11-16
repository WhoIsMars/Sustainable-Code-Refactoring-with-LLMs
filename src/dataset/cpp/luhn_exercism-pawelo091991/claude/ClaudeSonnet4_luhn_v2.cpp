#include "luhn.h"
#include <string>

using std::string;

bool luhn::valid(string str) {
    // Early validation and space removal in single pass
    string cleaned;
    cleaned.reserve(str.length());
    
    for (char c : str) {
        if (c == ' ') continue;
        if (c < '0' || c > '9') return false;
        cleaned.push_back(c);
    }
    
    if (cleaned.length() <= 1) return false;
    
    int sum = 0;
    bool alternate = false;
    
    // Process from right to left without reversing
    for (int i = cleaned.length() - 1; i >= 0; --i) {
        int digit = cleaned[i] - '0';
        
        if (alternate) {
            digit *= 2;
            if (digit > 9) digit -= 9;
        }
        
        sum += digit;
        alternate = !alternate;
    }
    
    return sum % 10 == 0;
}
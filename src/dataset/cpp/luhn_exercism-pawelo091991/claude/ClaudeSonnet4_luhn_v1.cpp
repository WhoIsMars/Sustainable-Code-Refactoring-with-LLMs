#include "luhn.h"
#include <string>

using std::string;

bool luhn::valid(string str) {
    // Remove spaces in-place without creating temporary objects
    size_t write_pos = 0;
    for (size_t read_pos = 0; read_pos < str.length(); ++read_pos) {
        if (str[read_pos] != ' ') {
            str[write_pos++] = str[read_pos];
        }
    }
    str.resize(write_pos);
    
    if (str.length() <= 1)
        return false;
    
    int sum = 0;
    bool double_digit = false;
    
    // Process from right to left without reversing
    for (int i = str.length() - 1; i >= 0; --i) {
        char c = str[i];
        if (c < '0' || c > '9')
            return false;
        
        int digit = c - '0';
        
        if (double_digit) {
            digit *= 2;
            if (digit > 9)
                digit -= 9;
        }
        
        sum += digit;
        double_digit = !double_digit;
    }
    
    return sum % 10 == 0;
}
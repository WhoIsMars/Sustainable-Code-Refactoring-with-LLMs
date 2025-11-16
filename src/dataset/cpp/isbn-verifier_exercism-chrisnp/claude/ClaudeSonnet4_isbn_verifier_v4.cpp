#include "isbn_verifier.h"

using std::string;

bool isbn_verifier::is_valid(string const& isbn) noexcept {
    int position = 10;
    int csum = 0;
    
    for (const char c : isbn) {
        if (c == '-') continue;
        
        int digit_val;
        if (c == 'X') {
            if (position != 1) return false;
            digit_val = 10;
        } else if (c >= '0' && c <= '9') {
            digit_val = c - '0';
        } else {
            return false;
        }
        
        csum += digit_val * position--;
    }
    
    return position == 0 && csum % 11 == 0;
}
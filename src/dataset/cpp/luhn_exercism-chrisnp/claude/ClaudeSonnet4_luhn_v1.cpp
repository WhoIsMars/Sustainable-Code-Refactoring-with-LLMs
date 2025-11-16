#include "luhn.h"
#include <algorithm>

using namespace std;

bool luhn::valid( string num ) {
    if (num.length() < 2) return false;
    
    int csum = 0;
    int digitCount = 0;
    
    for (int i = num.length() - 1; i >= 0; --i) {
        char c = num[i];
        if (c == ' ') continue;
        
        if (c < '0' || c > '9') return false;
        
        int d = c - '0';
        if (digitCount & 1) {
            d <<= 1;
            if (d > 9) d -= 9;
        }
        csum += d;
        ++digitCount;
    }
    
    return digitCount >= 2 && (csum % 10) == 0;
}
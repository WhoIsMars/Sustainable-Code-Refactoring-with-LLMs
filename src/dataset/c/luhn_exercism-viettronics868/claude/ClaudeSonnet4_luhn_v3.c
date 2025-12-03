#include "luhn.h"
#include <stdbool.h>
#include <ctype.h>

bool luhn(const char *num) {
    if (!num || !*num) return false;
    
    int sum = 0;
    int digit_count = 0;
    bool is_second = false;
    
    const char *p = num;
    while (*p) {
        if (isspace(*p)) {
            p++;
            continue;
        }
        if (!isdigit(*p)) return false;
        digit_count++;
        p++;
    }
    
    if (digit_count <= 1) return false;
    
    p = num;
    while (*p) {
        if (isspace(*p)) {
            p++;
            continue;
        }
        
        digit_count--;
        int digit = *p - '0';
        
        if (digit_count % 2 == 1) {
            digit *= 2;
            if (digit > 9) digit -= 9;
        }
        
        sum += digit;
        p++;
    }
    
    return sum % 10 == 0;
}
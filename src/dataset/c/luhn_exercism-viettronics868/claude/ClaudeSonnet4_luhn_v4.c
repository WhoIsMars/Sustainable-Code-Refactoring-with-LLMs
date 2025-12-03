#include "luhn.h"
#include <stdbool.h>
#include <ctype.h>

bool luhn(const char *num) {
    if (!num || !*num) return false;
    
    int sum = 0;
    int digit_count = 0;
    bool alternate = false;
    
    const char *end = num;
    while (*end) end++;
    end--;
    
    while (end >= num) {
        if (isspace(*end)) {
            end--;
            continue;
        }
        
        if (!isdigit(*end)) return false;
        
        int digit = *end - '0';
        digit_count++;
        
        if (alternate) {
            digit <<= 1;
            if (digit > 9) digit -= 9;
        }
        
        sum += digit;
        alternate = !alternate;
        end--;
    }
    
    return digit_count > 1 && sum % 10 == 0;
}
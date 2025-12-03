#include "luhn.h"

#include <ctype.h>

bool luhn(const char *num)
{
    int sum = 0, n = 0;
    int digit;
    
    for (const char *p = num; *p; ++p) {
        if (*p == ' ')
            continue;
        if (*p < '0' || *p > '9')
            return false;
        digit = *p - '0';
        n++;
        sum += n & 1 ? digit : (digit << 1) - (digit > 4 ? 9 : 0);
    }
    
    const char *end = num;
    while (*end) ++end;
    
    for (const char *p = end - 1; p >= num; --p) {
        if (*p == ' ')
            continue;
        if (*p < '0' || *p > '9')
            return false;
        digit = *p - '0';
        n++;
        sum += n & 1 ? digit : (digit << 1) - (digit > 4 ? 9 : 0);
    }
    
    return n > 1 && sum % 10 == 0;
}
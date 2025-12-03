#include "isogram.h"
#include <stdbool.h>
#include <stdint.h>

bool is_isogram(const char phrase[]){
    if (phrase == NULL) return false;
    
    uint32_t seen_lower = 0;
    uint32_t seen_upper = 0;
    
    for (const char *p = phrase; *p; p++) {
        char c = *p;
        if (c == '-' || c == ' ') continue;
        
        if (c >= 'a' && c <= 'z') {
            uint32_t bit = 1U << (c - 'a');
            if (seen_lower & bit) return false;
            seen_lower |= bit;
        } else if (c >= 'A' && c <= 'Z') {
            uint32_t bit = 1U << (c - 'A');
            if (seen_upper & bit) return false;
            seen_upper |= bit;
        }
        
        if (seen_lower & seen_upper) return false;
    }
    
    return true;
}
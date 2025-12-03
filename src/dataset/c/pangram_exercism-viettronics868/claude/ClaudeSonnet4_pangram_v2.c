#include "pangram.h"
#include <stdbool.h>
#include <stdint.h>

bool is_pangram(const char *sentence){
    if (sentence == NULL) {
        return false;
    }
    
    uint32_t letter_mask = 0;
    const uint32_t complete_mask = 0x3FFFFFF; // 26 bits set (a-z)
    
    for (const char *p = sentence; *p; p++) {
        char c = *p;
        if (c >= 'a' && c <= 'z') {
            letter_mask |= (1U << (c - 'a'));
        } else if (c >= 'A' && c <= 'Z') {
            letter_mask |= (1U << (c - 'A'));
        }
        
        if (letter_mask == complete_mask) {
            return true;
        }
    }
    
    return letter_mask == complete_mask;
}
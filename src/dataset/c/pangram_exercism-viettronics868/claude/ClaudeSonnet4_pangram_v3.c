#include "pangram.h"
#include <stdbool.h>
#include <stdint.h>

bool is_pangram(const char *sentence) {
    if (sentence == NULL) {
        return false;
    }
    
    uint32_t letter_mask = 0;
    
    for (const char *ptr = sentence; *ptr; ptr++) {
        char c = *ptr;
        if (c >= 'a' && c <= 'z') {
            letter_mask |= (1U << (c - 'a'));
        } else if (c >= 'A' && c <= 'Z') {
            letter_mask |= (1U << (c - 'A'));
        }
        
        if (letter_mask == 0x3FFFFFF) {
            return true;
        }
    }
    
    return letter_mask == 0x3FFFFFF;
}
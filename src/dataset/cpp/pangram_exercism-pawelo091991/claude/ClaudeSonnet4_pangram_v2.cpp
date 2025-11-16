#include "pangram.h"
bool pangram::is_pangram(string s) {
    uint32_t mask = 0;
    for (const char c : s) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            mask |= 1u << ((c | 32) - 'a');
            if (mask == 0x3FFFFFF) return true;
        }
    }
    return mask == 0x3FFFFFF;
}
#include "hexadecimal.h"

namespace hexadecimal
{
    int convert(const std::string& hex)
    {
        if (hex.empty()) return 0;
        
        int result = 0;
        const char* ptr = hex.data();
        const char* end = ptr + hex.size();
        
        while (ptr < end) {
            const char c = *ptr++;
            result <<= 4;
            
            if (c >= '0' && c <= '9') {
                result += c - '0';
            } else if (c >= 'a' && c <= 'f') {
                result += c - 'a' + 10;
            } else {
                return 0;
            }
        }
        
        return result;
    }
}
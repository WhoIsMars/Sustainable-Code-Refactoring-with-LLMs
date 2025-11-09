#include "hexadecimal.h"

namespace hexadecimal
{
    int convert(std::string hex)
    {
        if (hex.empty()) return 0;
        
        int result = 0;
        const int l = hex.length();
        
        for (int i = 0; i < l; ++i)
        {
            result <<= 4; // Equivalent to result *= 16, but faster
            
            const char c = hex[i];
            if (c >= '0' && c <= '9')
                result += c - '0';
            else if (c >= 'a' && c <= 'f')
                result += c - 'a' + 10;
            else
                return 0;
        }
        return result;
    }
} // namespace hexadecimal
#include "hexadecimal.h"

namespace hexadecimal
{
    int convert(const std::string& hex)
    {
        if (hex.empty()) return 0;
        
        int result = 0;
        const size_t length = hex.length();
        
        for (size_t i = 0; i < length; ++i)
        {
            const char c = hex[i];
            int digit;
            
            if (c >= '0' && c <= '9')
                digit = c - '0';
            else if (c >= 'a' && c <= 'f')
                digit = c - 'a' + 10;
            else if (c >= 'A' && c <= 'F')
                digit = c - 'A' + 10;
            else
                return 0;
            
            result = (result << 4) + digit;
        }
        return result;
    }
} // namespace hexadecimal
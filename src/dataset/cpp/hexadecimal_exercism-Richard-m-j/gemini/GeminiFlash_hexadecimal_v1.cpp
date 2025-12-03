#include "hexadecimal.h"
#include <algorithm>

namespace hexadecimal
{
    int convert(std::string hex)
    {
        int result = 0;
        for (char c : hex)
        {
            int digit;
            if (c >= '0' && c <= '9')
            {
                digit = c - '0';
            }
            else if (c >= 'a' && c <= 'f')
            {
                digit = c - 'a' + 10;
            }
            else if (c >= 'A' && c <= 'F')
            {
                digit = c - 'A' + 10;
            }
            else
            {
                return 0;
            }
            if (result > (INT_MAX / 16)) return 0; // Check for potential overflow before multiplication
            result = result * 16 + digit;
        }
        return result;
    }
} // namespace hexadecimal
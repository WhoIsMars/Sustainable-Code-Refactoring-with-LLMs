#include "hexadecimal.h"
#include <algorithm>
#include <cctype>

namespace hexadecimal
{
    int convert(std::string hex)
    {
        int result = 0;
        for (char c : hex)
        {
            c = std::tolower(c);
            int digit;
            if (c >= '0' && c <= '9')
            {
                digit = c - '0';
            }
            else if (c >= 'a' && c <= 'f')
            {
                digit = c - 'a' + 10;
            }
            else
            {
                return 0;
            }
            if (result > (INT_MAX / 16)) return 0;
            result = (result << 4) | digit;
        }
        return result;
    }
} // namespace hexadecimal
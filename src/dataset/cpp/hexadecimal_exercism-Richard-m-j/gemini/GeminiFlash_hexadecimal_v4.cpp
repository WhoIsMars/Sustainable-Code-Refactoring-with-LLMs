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
            int digit;
            if (std::isdigit(c))
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

            if (result > (INT_MAX / 16)) return 0;

            result = result * 16 + digit;
        }
        return result;
    }
} // namespace hexadecimal
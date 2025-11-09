#include "hexadecimal.h"

namespace hexadecimal
{
    int convert(std::string hex)
    {
        int result = 0;
        int l = hex.length();
        for (int i = 0; i < l; i++)
        {
            result *= 16;
            if (hex[i] >= '0' && hex[i] <= '9')
                result += hex[i] - '0';
            else if (hex[i] >= 'a' && hex[i] <= 'f')
                result += hex[i] - 'a' + 10;
            else
                return 0;
        }
        return result;
    }
} // namespace hexadecimal

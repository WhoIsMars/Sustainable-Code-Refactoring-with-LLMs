#include "hexadecimal.h"
#include <cctype>

namespace hexadecimal
{
    int convert(const std::string& hex)
    {
        int result = 0;
        for (char c : hex)
        {
            if (std::isdigit(c))
                result = (result << 4) + (c - '0');
            else if (std::islower(c) && c >= 'a' && c <= 'f')
                result = (result << 4) + (c - 'a' + 10);
            else
                return 0;
        }
        return result;
    }
} // namespace hexadecimal
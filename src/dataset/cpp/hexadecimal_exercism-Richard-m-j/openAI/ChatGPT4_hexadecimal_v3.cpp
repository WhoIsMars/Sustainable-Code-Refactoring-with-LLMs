#include "hexadecimal.h"
#include <cctype>

namespace hexadecimal
{
    int convert(const std::string& hex)
    {
        int result = 0;
        for (char c : hex)
        {
            result *= 16;
            if (std::isdigit(c))
                result += c - '0';
            else if (std::isxdigit(c) && std::islower(c))
                result += c - 'a' + 10;
            else
                return 0;
        }
        return result;
    }
} // namespace hexadecimal
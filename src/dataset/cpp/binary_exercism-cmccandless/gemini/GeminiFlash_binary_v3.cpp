#include "binary.h"

int binary::convert(std::string s)
{
    int result = 0;
    size_t len = s.length();

    for (size_t i = 0; i < len; ++i)
    {
        char ch = s[i];
        result <<= 1;
        if (ch == '1')
        {
            result |= 1;
        }
        else if (ch != '0')
        {
            return 0;
        }
    }
    return result;
}
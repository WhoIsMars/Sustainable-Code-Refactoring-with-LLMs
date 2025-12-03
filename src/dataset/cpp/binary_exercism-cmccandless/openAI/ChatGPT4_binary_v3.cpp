#include "binary.h"

int binary::convert(const std::string& s)
{
    int result = 0;
    for (char ch : s)
    {
        if (ch == '1') 
        {
            result = (result << 1) | 1;
        }
        else if (ch == '0') 
        {
            result <<= 1;
        }
        else 
        {
            return 0;
        }
    }
    return result;
}
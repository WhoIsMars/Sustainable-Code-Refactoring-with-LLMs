#include "raindrops.h"
#include <string>

namespace raindrops
{
    std::string convert(int num)
    {
        std::string result;
        result.reserve(15); // Reserve space for "PlingPlangPlong"
        
        if (num % 3 == 0)
        {
            result += "Pling";
        }
        if (num % 5 == 0)
        {
            result += "Plang";
        }
        if (num % 7 == 0)
        {
            result += "Plong";
        }

        return result.empty() ? std::to_string(num) : result;
    }
} // namespace raindrops
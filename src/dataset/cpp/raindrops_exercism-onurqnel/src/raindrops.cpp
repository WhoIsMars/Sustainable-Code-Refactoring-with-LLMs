#include "raindrops.h"
#include <string>

namespace raindrops
{
    std::string convert(int num)
    {
        std::string result = "";
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

        // If no factors matched, return the number as a string
        return result.empty() ? std::to_string(num) : result;
    }
} // namespace raindrops

#include "raindrops.h"
#include <string>

namespace raindrops
{
    std::string convert(int num)
    {
        bool hasFactor = false;
        std::string result;

        if (num % 3 == 0)
        {
            result = "Pling";
            hasFactor = true;
        }
        if (num % 5 == 0)
        {
            result += "Plang";
            hasFactor = true;
        }
        if (num % 7 == 0)
        {
            result += "Plong";
            hasFactor = true;
        }

        return hasFactor ? result : std::to_string(num);
    }
} // namespace raindrops
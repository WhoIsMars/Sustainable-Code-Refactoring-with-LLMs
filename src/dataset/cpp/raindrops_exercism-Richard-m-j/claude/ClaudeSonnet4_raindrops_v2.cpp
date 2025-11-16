#include "raindrops.h"

namespace raindrops
{
    std::string raindrops(int number)
    {
        std::string result;
        result.reserve(15); // Reserve space for "PlingPlangPlong"
        
        if (number % 3 == 0)
            result += "Pling";
        if (number % 5 == 0)
            result += "Plang";
        if (number % 7 == 0)
            result += "Plong";
        
        if (result.empty())
            result = std::to_string(number);
        
        return result;
    }
}
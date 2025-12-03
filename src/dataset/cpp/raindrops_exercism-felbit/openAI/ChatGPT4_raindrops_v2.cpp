#include "raindrops.h"

namespace raindrops
{
    std::string convert(int number)
    {
        if (number % 3 == 0 || number % 5 == 0 || number % 7 == 0)
        {
            std::string result;
            if (number % 3 == 0) result += "Pling";
            if (number % 5 == 0) result += "Plang";
            if (number % 7 == 0) result += "Plong";
            return result;
        }
        return std::to_string(number);
    }
}
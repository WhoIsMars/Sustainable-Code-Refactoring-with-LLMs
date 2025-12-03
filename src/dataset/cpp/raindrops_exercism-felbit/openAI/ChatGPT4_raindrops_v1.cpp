#include "raindrops.h"

namespace raindrops
{
    std::string convert(int number)
    {
        const bool divisible_by_3 = (number % 3 == 0);
        const bool divisible_by_5 = (number % 5 == 0);
        const bool divisible_by_7 = (number % 7 == 0);

        if (!divisible_by_3 && !divisible_by_5 && !divisible_by_7) 
        {
            return std::to_string(number);
        }

        std::string result;
        if (divisible_by_3) result += "Pling";
        if (divisible_by_5) result += "Plang";
        if (divisible_by_7) result += "Plong";

        return result;
    }
}
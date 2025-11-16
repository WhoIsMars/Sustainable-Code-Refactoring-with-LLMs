#include "raindrops.h"
#include <string>

namespace raindrops
{
    std::string convert(int num)
    {
        bool divisible_by_3 = (num % 3 == 0);
        bool divisible_by_5 = (num % 5 == 0);
        bool divisible_by_7 = (num % 7 == 0);

        if (!divisible_by_3 && !divisible_by_5 && !divisible_by_7)
        {
            return std::to_string(num);
        }

        std::string result;
        if (divisible_by_3) result = "Pling";
        if (divisible_by_5) result += "Plang";
        if (divisible_by_7) result += "Plong";

        return result;
    }
} // namespace raindrops
#include "raindrops.h"

namespace raindrops
{
    std::string raindrops(int number)
    {
        std::string result;
        if (number % 3 == 0) result.append("Pling");
        if (number % 5 == 0) result.append("Plang");
        if (number % 7 == 0) result.append("Plong");
        return result.empty() ? std::to_string(number) : result;
    }
} // namespace raindrops
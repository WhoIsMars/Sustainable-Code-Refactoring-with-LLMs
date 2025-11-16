#include "raindrops.h"

namespace raindrops
{
    std::string convert(int number)
    {
        std::string result;
        result.reserve(15);

        const bool div3 = (number % 3 == 0);
        const bool div5 = (number % 5 == 0);
        const bool div7 = (number % 7 == 0);

        if (div3) result += "Pling";
        if (div5) result += "Plang";
        if (div7) result += "Plong";

        if (!(div3 || div5 || div7)) {
            result = std::to_string(number);
        }

        return result;
    }
}
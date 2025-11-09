#include "raindrops.h"

namespace raindrops
{
    std::string raindrops(int number)
    {
        std::string result = "";
        if (!(number % 3))
            result += "Pling";
        if (!(number % 5))
            result += "Plang";
        if (!(number % 7))
            result += "Plong";
        if (result == "")
            result = "" + number;
        return result;
    }
} // namespace raindrops

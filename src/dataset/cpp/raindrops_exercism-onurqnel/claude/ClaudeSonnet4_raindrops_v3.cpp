#include "raindrops.h"
#include <string>

namespace raindrops
{
    std::string convert(int num)
    {
        std::string result;
        
        const bool div3 = (num % 3 == 0);
        const bool div5 = (num % 5 == 0);
        const bool div7 = (num % 7 == 0);
        
        if (div3 || div5 || div7) {
            result.reserve(15);
            if (div3) result += "Pling";
            if (div5) result += "Plang";
            if (div7) result += "Plong";
            return result;
        }
        
        return std::to_string(num);
    }
}
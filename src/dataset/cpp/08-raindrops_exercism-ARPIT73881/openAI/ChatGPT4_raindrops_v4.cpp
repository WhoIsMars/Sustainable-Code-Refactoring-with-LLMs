#include "raindrops.h"
#include <string>

namespace raindrops {

    std::string convert(int number) {
        bool divisibleBy3 = (number % 3 == 0);
        bool divisibleBy5 = (number % 5 == 0);
        bool divisibleBy7 = (number % 7 == 0);

        if (!divisibleBy3 && !divisibleBy5 && !divisibleBy7) {
            return std::to_string(number);
        }

        std::string result;
        if (divisibleBy3) result += "Pling";
        if (divisibleBy5) result += "Plang";
        if (divisibleBy7) result += "Plong";

        return result;
    }

}  // namespace raindrops
#include "raindrops.h"

namespace raindrops {
    std::string convert(int n) {
        bool divisibleBy3 = (n % 3 == 0);
        bool divisibleBy5 = (n % 5 == 0);
        bool divisibleBy7 = (n % 7 == 0);

        if (!divisibleBy3 && !divisibleBy5 && !divisibleBy7) {
            return std::to_string(n);
        }

        std::string result;
        if (divisibleBy3) result = "Pling";
        if (divisibleBy5) result += "Plang";
        if (divisibleBy7) result += "Plong";

        return result;
    }
}
#include "raindrops.h"

namespace raindrops {
    std::string convert(int n) {
        bool divisible = false;
        std::string result;
        if (n % 3 == 0) {
            result = "Pling";
            divisible = true;
        }
        if (n % 5 == 0) {
            result += "Plang";
            divisible = true;
        }
        if (n % 7 == 0) {
            result += "Plong";
            divisible = true;
        }
        return divisible ? result : std::to_string(n);
    }
}
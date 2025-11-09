#include "raindrops.h"
#include <string>

namespace raindrops {

    std::string convert(int number) {
        bool hasFactor = false;
        std::string result;

        if (number % 3 == 0) {
            result = "Pling";
            hasFactor = true;
        }
        if (number % 5 == 0) {
            result += "Plang";
            hasFactor = true;
        }
        if (number % 7 == 0) {
            result += "Plong";
            hasFactor = true;
        }

        return hasFactor ? result : std::to_string(number);
    }

}  // namespace raindrops
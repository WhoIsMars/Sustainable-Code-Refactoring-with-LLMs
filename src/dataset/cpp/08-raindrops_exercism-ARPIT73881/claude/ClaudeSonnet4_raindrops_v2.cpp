#include "raindrops.h"
#include <string>

namespace raindrops {

    std::string convert(int number) {
        std::string result;
        result.reserve(15); // Reserve space for "PlingPlangPlong"

        bool hasFactor = false;

        if (number % 3 == 0) {
            result += "Pling";
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

        if (!hasFactor) {
            result = std::to_string(number);
        }

        return result;
    }

}  // namespace raindrops
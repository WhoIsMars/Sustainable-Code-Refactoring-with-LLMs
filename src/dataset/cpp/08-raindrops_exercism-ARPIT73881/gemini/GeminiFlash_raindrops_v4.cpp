#include "raindrops.h"
#include <string>
#include <sstream>

namespace raindrops {

    std::string convert(int number) {
        std::stringstream result;

        if (number % 3 == 0) {
            result << "Pling";
        }
        if (number % 5 == 0) {
            result << "Plang";
        }
        if (number % 7 == 0) {
            result << "Plong";
        }

        if (result.tellp() == 0) {
            result << number;
        }

        return result.str();
    }

}  // namespace raindrops
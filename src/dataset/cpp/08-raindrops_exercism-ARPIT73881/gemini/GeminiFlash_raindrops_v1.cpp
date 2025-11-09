#include "raindrops.h"
#include <string>
#include <sstream>

namespace raindrops {

std::string convert(int number) {
    std::stringstream result;
    bool converted = false;

    if (number % 3 == 0) {
        result << "Pling";
        converted = true;
    }
    if (number % 5 == 0) {
        result << "Plang";
        converted = true;
    }
    if (number % 7 == 0) {
        result << "Plong";
        converted = true;
    }

    if (!converted) {
        result << number;
    }

    return result.str();
}

}  // namespace raindrops
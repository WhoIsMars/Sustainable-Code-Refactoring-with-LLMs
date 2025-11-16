#include "raindrops.h"
#include <sstream>

namespace raindrops {

std::string convert(int number) {
    std::ostringstream raindrops;

    if (number % 3 == 0) {
        raindrops << "Pling";
    }

    if (number % 5 == 0) {
        raindrops << "Plang";
    }

    if (number % 7 == 0) {
        raindrops << "Plong";
    }

    std::string result = raindrops.str();
    return result.empty() ? std::to_string(number) : result;
}

} // namespace raindrops
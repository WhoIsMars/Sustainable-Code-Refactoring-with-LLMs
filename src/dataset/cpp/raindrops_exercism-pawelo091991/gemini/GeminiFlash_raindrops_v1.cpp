#include "raindrops.h"
#include <string>

std::string raindrops::convert(int number) {
    std::string result;
    result.reserve(20); // Pre-allocate memory to avoid reallocations

    if (number % 3 == 0) {
        result += "Pling";
    }
    if (number % 5 == 0) {
        result += "Plang";
    }
    if (number % 7 == 0) {
        result += "Plong";
    }

    if (result.empty()) {
        return std::to_string(number);
    } else {
        return result;
    }
}
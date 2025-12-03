#include "raindrops.h"
#include <string>

string raindrops::convert(int number) {
    std::string raindrops;

    if (number % 3 == 0) raindrops += "Pling";
    if (number % 5 == 0) raindrops += "Plang";
    if (number % 7 == 0) raindrops += "Plong";

    return raindrops.empty() ? std::to_string(number) : raindrops;
}
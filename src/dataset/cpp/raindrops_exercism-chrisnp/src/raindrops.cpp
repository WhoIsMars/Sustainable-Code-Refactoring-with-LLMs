#include "raindrops.h"

#include <sstream>

std::string raindrops::convert(int n) {
    stringstream sounds {};
    for (auto drop : raindrops::drops)
        if (n % drop.first == 0) sounds << drop.second;
    string rainsong = sounds.str();
    return rainsong.empty() ? to_string(n) : rainsong;
}

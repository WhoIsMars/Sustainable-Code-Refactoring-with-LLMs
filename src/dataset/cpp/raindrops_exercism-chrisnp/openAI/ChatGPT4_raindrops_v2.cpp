#include "raindrops.h"
#include <string>

std::string raindrops::convert(int n) {
    std::string rainsong;
    for (const auto& drop : raindrops::drops) {
        if (n % drop.first == 0) {
            rainsong += drop.second;
        }
    }
    return rainsong.empty() ? std::to_string(n) : rainsong;
}
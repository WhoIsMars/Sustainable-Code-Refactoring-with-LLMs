#include "raindrops.h"

std::string raindrops::convert(int n) {
    std::string result;
    result.reserve(32);
    
    for (const auto& drop : raindrops::drops) {
        if (n % drop.first == 0) {
            result += drop.second;
        }
    }
    
    return result.empty() ? std::to_string(n) : result;
}
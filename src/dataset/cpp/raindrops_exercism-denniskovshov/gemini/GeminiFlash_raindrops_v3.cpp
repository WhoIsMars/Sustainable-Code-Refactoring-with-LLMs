#include <string>
#include <sstream>
#include "raindrops.h"

namespace raindrops {
    std::string convert(int num) {
        std::stringstream result;
        bool has_factor = false;

        if (num % 3 == 0) {
            result << "Pling";
            has_factor = true;
        }
        
        if (num % 5 == 0) {
            result << "Plang";
            has_factor = true;
        }

        if (num % 7 == 0) {
            result << "Plong";
            has_factor = true;
        }

        if (!has_factor) {
            result << num;
        }

        return result.str();
    }
}  // namespace raindrops
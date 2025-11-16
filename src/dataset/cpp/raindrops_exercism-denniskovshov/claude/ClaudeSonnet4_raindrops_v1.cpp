#include <string>
#include "raindrops.h"

namespace raindrops {
    std::string convert(int num) {
        std::string result;
        result.reserve(15); // Reserve space for "PlingPlangPlong"
        
        bool has_factor = false;

        if (num % 3 == 0) {
            result += "Pling";
            has_factor = true;
        }
        
        if (num % 5 == 0) {
            result += "Plang";
            has_factor = true;
        }

        if (num % 7 == 0) {
            result += "Plong";
            has_factor = true;
        }

        if (!has_factor) {
            return std::to_string(num);
        }

        return result;
    }
}  // namespace raindrops
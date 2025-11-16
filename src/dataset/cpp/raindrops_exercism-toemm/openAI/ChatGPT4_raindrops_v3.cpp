#include "raindrops.h"
#include <string>

namespace raindrops {

    std::string convert(int i) {
        std::string result;

        if (i % 3 == 0) result += "Pling";
        if (i % 5 == 0) result += "Plang";
        if (i % 7 == 0) result += "Plong";

        return result.empty() ? std::to_string(i) : result;
    }

}  // namespace raindrops
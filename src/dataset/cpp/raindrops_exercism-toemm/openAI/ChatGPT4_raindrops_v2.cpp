#include "raindrops.h"
#include <string>

namespace raindrops {

    std::string convert(int i) {
        std::string str;

        bool divisible_by_3 = (i % 3 == 0);
        bool divisible_by_5 = (i % 5 == 0);
        bool divisible_by_7 = (i % 7 == 0);

        if (divisible_by_3) str += "Pling";
        if (divisible_by_5) str += "Plang";
        if (divisible_by_7) str += "Plong";

        return str.empty() ? std::to_string(i) : str;
    }

}  // namespace raindrops
#include "raindrops.h"

namespace raindrops {

    std::string convert(int drops) {
        std::string sound;

        if (drops % 3 == 0) sound += "Pling";
        if (drops % 5 == 0) sound += "Plang";
        if (drops % 7 == 0) sound += "Plong";

        return sound.empty() ? std::to_string(drops) : sound;
    }

}  // namespace raindrops
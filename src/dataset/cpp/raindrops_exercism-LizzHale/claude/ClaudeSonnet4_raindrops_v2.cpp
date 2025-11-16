#include "raindrops.h"

namespace raindrops {

    std::string convert(int drops) {
        std::string sound;
        sound.reserve(15); // Reserve space for "PlingPlangPlong"

        if (drops % 3 == 0) {
            sound += "Pling";
        }
        if (drops % 5 == 0) {
            sound += "Plang";
        }
        if (drops % 7 == 0) {
            sound += "Plong";
        }

        if (sound.empty()) {
            return std::to_string(drops);
        }
        return sound;
    }

}  // namespace raindrops
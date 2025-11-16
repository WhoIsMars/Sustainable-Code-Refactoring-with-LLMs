#include "raindrops.h"

namespace raindrops {

    std::string convert(int drops) {
        std::string sound = "";

        if (drops % 3 == 0) {
            sound = sound + "Pling";
        }
        if (drops % 5 == 0) {
            sound = sound + "Plang";
        }
        if (drops % 7 == 0) {
            sound = sound + "Plong";
        }

        if (std::empty(sound)) {
            return std::to_string(drops);
        }
        return sound;
    }

}  // namespace raindrops

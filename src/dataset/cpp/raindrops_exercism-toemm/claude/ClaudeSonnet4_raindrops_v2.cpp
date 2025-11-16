#include "raindrops.h"
#include <string>

namespace raindrops {

    std::string convert(int i) {
        std::string str;
        str.reserve(15); // Reserve space for "PlingPlangPlong"
        
        if (i % 3 == 0) {
            str += "Pling";
        }
        if (i % 5 == 0) {
            str += "Plang";
        }
        if (i % 7 == 0) {
            str += "Plong";
        }
        
        if (str.empty()) {
            str = std::to_string(i);
        }
        
        return str;
    }

}  // namespace raindrops
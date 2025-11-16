#include "raindrops.h"
#include <string>
#include <iostream>

namespace raindrops {

// TODO: add your solution here
    std::string convert(int i) {

        std::string str;;
        if (i % 3 == 0) {
            str += "Pling";
        }

        if (i % 5 == 0) {
            str += "Plang";
        }

        if (i % 7 == 0) {
            str += "Plong";
        }

        if (str == "") {
            str = std::to_string(i);
        }

        printf("Input: %i, Output: %s\n", i, str.c_str());
        return str;


    }

}  // namespace raindrops

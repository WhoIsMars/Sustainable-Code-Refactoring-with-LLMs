#include "beer_song.h"

#include <string>
#include <algorithm>

namespace beer_song {

std::string verse(int i) {
    if (i == 0) {
        return "No more bottles of beer on the wall, no more bottles of beer.\n"
               "Go to the store and buy some more, 99 bottles of beer on the wall.\n";
    }

    std::string result;
    result.reserve(256); 

    result += std::to_string(i);
    result += (i == 1) ? " bottle" : " bottles";
    result += " of beer on the wall, ";
    result += std::to_string(i);
    result += (i == 1) ? " bottle" : " bottles";
    result += " of beer.\nTake ";
    result += (i == 1) ? "it" : "one";
    result += " down and pass it around, ";

    if (i == 1) {
        result += "no more";
    } else {
        result += std::to_string(i - 1);
    }

    result += " bottle";
    if (i != 2) {
        result += "s";
    }
    result += " of beer on the wall.\n";

    return result;
}


std::string sing(int begin, int ending) {
    std::string out;
    int num_verses = begin - ending + 1;
    out.reserve(num_verses * 256);

    for (int i = begin; i >= ending; --i) {
        out += verse(i);
        if (i != ending) {
            out += "\n";
        }
    }

    return out;
}

}  // namespace beer_song
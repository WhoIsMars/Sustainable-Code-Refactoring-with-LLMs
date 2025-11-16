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
    if (i == 1) {
        result = "1 bottle of beer on the wall, 1 bottle of beer.\n"
                 "Take it down and pass it around, no more bottles of beer on the wall.\n";
    } else {
        result = std::to_string(i) + " bottles of beer on the wall, " + std::to_string(i) + " bottles of beer.\n"
                 "Take one down and pass it around, " + std::to_string(i - 1) + " bottle" + ((i == 2) ? "" : "s") + " of beer on the wall.\n";
    }
    return result;
}


std::string sing(int begin, int ending) {
    std::string out;
    for (int i = begin; i >= ending; --i) {
        out += verse(i);
        if (i != ending) {
            out += "\n";
        }
    }
    return out;
}

}  // namespace beer_song
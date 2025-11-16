#include "beer_song.h"

#include <string>
#include <sstream>

namespace beer_song {

std::string verse(int i) {
    if (i == 0) {
        return "No more bottles of beer on the wall, no more bottles of beer.\n"
               "Go to the store and buy some more, 99 bottles of beer on the wall.\n";
    }

    std::string bottles = (i == 1) ? " bottle" : " bottles";
    std::string take_down = (i == 1) ? "it" : "one";
    std::string next_bottles = (i == 1) ? "no more" : std::to_string(i - 1);
    std::string next_bottles_plural = (i == 2) ? "" : "s";

    std::ostringstream out;
    out << i << bottles << " of beer on the wall, " << i << bottles << " of beer.\n"
        << "Take " << take_down << " down and pass it around, " << next_bottles << " bottle"
        << next_bottles_plural << " of beer on the wall.\n";

    return out.str();
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
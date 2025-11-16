#include "beer_song.h"

#include <sstream>
#include <string>

namespace beer_song {

std::string verse(int i) {
    if (i == 0) {
        return "No more bottles of beer on the wall, no more bottles of beer.\n"
               "Go to the store and buy some more, 99 bottles of beer on the wall.\n";
    }

    std::string bottle_word = (i == 1) ? "bottle" : "bottles";
    std::string next_bottle_word = (i - 1 == 1) ? "bottle" : "bottles";
    std::string next_count = (i - 1 == 0) ? "no more" : std::to_string(i - 1);

    return std::to_string(i) + " " + bottle_word + " of beer on the wall, " +
           std::to_string(i) + " " + bottle_word + " of beer.\n" +
           "Take " + ((i == 1) ? "it" : "one") + " down and pass it around, " +
           next_count + " " + next_bottle_word + " of beer on the wall.\n";
}

std::string sing(int begin, int ending) {
    std::ostringstream out;
    for (int i = begin; i >= ending; --i) {
        out << verse(i);
        if (i != ending) out << "\n";
    }
    return out.str();
}

}  // namespace beer_song
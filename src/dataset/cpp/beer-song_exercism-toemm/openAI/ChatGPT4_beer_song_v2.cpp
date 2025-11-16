#include "beer_song.h"

#include <sstream>

namespace beer_song {

std::string verse(int i) {
    if (i == 0) {
        return "No more bottles of beer on the wall, no more bottles of beer.\n"
               "Go to the store and buy some more, 99 bottles of beer on the wall.\n";
    }

    std::ostringstream out;
    out << i << (i == 1 ? " bottle" : " bottles") << " of beer on the wall, " << i
        << (i == 1 ? " bottle" : " bottles") << " of beer.\n"
        << "Take " << (i == 1 ? "it" : "one") << " down and pass it around, "
        << (i - 1 == 0 ? "no more" : std::to_string(i - 1)) << " bottle"
        << (i - 1 == 1 ? "" : "s") << " of beer on the wall.\n";

    return out.str();
}

std::string sing(int begin, int ending) {
    std::ostringstream out;

    for (int i = begin; i >= ending; --i) {
        out << verse(i);
        if (i != ending) {
            out << '\n';
        }
    }

    return out.str();
}

}  // namespace beer_song
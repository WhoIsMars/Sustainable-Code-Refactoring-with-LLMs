#include "beer_song.h"
#include <string>
#include <sstream>

namespace beer_song {

std::string sing(int nbottels_start, int nbottels_stop) {
    std::string song;
    for (int i = nbottels_start; i >= nbottels_stop; --i) {
        song += verse(i);
        if (i > nbottels_stop) {
            song += "\n";
        }
    }
    return song;
}

std::string verse(int nbottels) {
    if (nbottels <= 0) {
        return "No more bottles of beer on the wall, no more bottles of beer.\n"
               "Go to the store and buy some more, 99 bottles of beer on the wall.\n";
    }

    std::string p1_nbottels = p1(nbottels);
    std::string p1_nbottels_minus_1 = p1(nbottels - 1);
    std::string p2_nbottels = p2(nbottels);

    std::string verse_string = p1_nbottels + " of beer on the wall, " + p1_nbottels + " of beer.\n" +
                               "Take " + p2_nbottels + " down and pass it around, " + p1_nbottels_minus_1 + " of beer on the wall.\n";

    return verse_string;
}


std::string p1(int nbottels) {
    switch (nbottels) {
        case 0: return "no more bottles";
        case 1: return "1 bottle";
        default: return std::to_string(nbottels) + " bottles";
    }
}

std::string p2(int nbottels) {
    return (nbottels == 1) ? "it" : "one";
}

} // namespace beer_song
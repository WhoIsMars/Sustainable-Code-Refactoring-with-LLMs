#include "beer_song.h"
#include <string>

namespace beer_song {

    std::string sing(int nbottels_start, int nbottels_stop) {
        std::string song;
        for (int i = nbottels_start; i >= nbottels_stop; --i) {
            song += verse(i);
            if (i > nbottels_stop) {
                song += '\n';
            }
        }
        return song;
    }

    std::string verse(int nbottels) {
        if (nbottels <= 0) {
            return "No more bottles of beer on the wall, no more bottles of beer.\n"
                   "Go to the store and buy some more, 99 bottles of beer on the wall.\n";
        }
        return p1(nbottels) + " of beer on the wall, " + p1(nbottels) + " of beer.\n" +
               "Take " + p2(nbottels) + " down and pass it around, " + p1(nbottels - 1) + " of beer on the wall.\n";
    }

    std::string p1(int nbottels) {
        if (nbottels == 0) return "no more bottles";
        if (nbottels == 1) return "1 bottle";
        return std::to_string(nbottels) + " bottles";
    }

    std::string p2(int nbottels) {
        return (nbottels == 1) ? "it" : "one";
    }

}  // namespace beer_song
#include "beer_song.h"
#include <string>

namespace beer_song {

    std::string sing(int nbottles_start, int nbottles_stop) {
        std::string song;
        for (int i = nbottles_start; i >= nbottles_stop; --i) {
            song += verse(i);
            if (i > nbottles_stop) {
                song += '\n';
            }
        }
        return song;
    }

    std::string verse(int nbottles) {
        if (nbottles == 0) {
            return "No more bottles of beer on the wall, no more bottles of beer.\n"
                   "Go to the store and buy some more, 99 bottles of beer on the wall.\n";
        }
        return p1(nbottles) + " of beer on the wall, " + p1(nbottles) + " of beer.\n" +
               "Take " + p2(nbottles) + " down and pass it around, " + p1(nbottles - 1) + " of beer on the wall.\n";
    }

    std::string p1(int nbottles) {
        if (nbottles == 0) return "no more bottles";
        if (nbottles == 1) return "1 bottle";
        return std::to_string(nbottles) + " bottles";
    }

    std::string p2(int nbottles) {
        return (nbottles == 1) ? "it" : "one";
    }

}  // namespace beer_song
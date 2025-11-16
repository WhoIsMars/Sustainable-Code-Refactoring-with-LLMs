#include "beer_song.h"
#include <iostream>
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

        std::string p1_val = p1(nbottels);
        std::string p2_val = p2(nbottels);
        std::string p1_minus_1_val = p1(nbottels - 1);

        std::string verse_str = p1_val + " of beer on the wall, " + p1_val + " of beer.\n"
                                 "Take " + p2_val + " down and pass it around, " + p1_minus_1_val + " of beer on the wall.\n";

        return verse_str;
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

}  // namespace beer_song
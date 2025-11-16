#include "beer_song.h"
#include <iostream>
#include <string>
#include <algorithm>

namespace beer_song {

    std::string sing(int nbottels_start, int nbottels_stop) {
        std::string song;
        song.reserve((nbottels_start - nbottels_stop + 1) * 200); // Pre-allocate memory to avoid reallocations

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
        std::string p2_nbottels = p2(nbottels);
        std::string p1_nbottels_minus_1 = p1(nbottels - 1);

        std::string verse_string;
        verse_string.reserve(150); // Pre-allocate memory

        verse_string += p1_nbottels;
        verse_string += " of beer on the wall, ";
        verse_string += p1_nbottels;
        verse_string += " of beer.\n";
        verse_string += "Take ";
        verse_string += p2_nbottels;
        verse_string += " down and pass it around, ";
        verse_string += p1_nbottels_minus_1;
        verse_string += " of beer on the wall.\n";

        return verse_string;
    }

    std::string p1(int nbottels) {
        switch (nbottels) {
            case 0: return "no more bottles";
            case 1: return "1 bottle";
            default: {
                // Use a static buffer to avoid repeated allocations
                static char buffer[12]; // Sufficient for numbers up to 999,999,999
                int length = snprintf(buffer, sizeof(buffer), "%d bottles", nbottels);
                return std::string(buffer, length);
            }
        }
    }

    std::string p2(int nbottels) {
        return (nbottels == 1) ? "it" : "one";
    }

}  // namespace beer_song
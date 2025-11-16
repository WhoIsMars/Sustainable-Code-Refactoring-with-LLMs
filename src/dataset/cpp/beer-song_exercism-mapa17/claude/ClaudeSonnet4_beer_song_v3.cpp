#include "beer_song.h"
#include <string>
#include <string_view>

namespace beer_song {
    
    std::string sing(int nbottels_start, int nbottels_stop) {
        std::string song;
        song.reserve((nbottels_start - nbottels_stop + 1) * 150);
        
        for (int i = nbottels_start; i >= nbottels_stop; i--) {
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
        
        std::string result;
        result.reserve(120);
        
        const std::string bottles_current = p1(nbottels);
        const std::string bottles_next = p1(nbottels - 1);
        const std::string take_action = p2(nbottels);
        
        result += bottles_current;
        result += " of beer on the wall, ";
        result += bottles_current;
        result += " of beer.\nTake ";
        result += take_action;
        result += " down and pass it around, ";
        result += bottles_next;
        result += " of beer on the wall.\n";
        
        return result;
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
#include "beer_song.h"
#include <string>
#include <sstream>

namespace beer_song {
    
    std::string sing(int nbottels_start, int nbottels_stop){
        std::ostringstream song;
        song.reserve(1024); // Pre-allocate reasonable buffer size
        
        for(int i = nbottels_start; i >= nbottels_stop; i--){
            song << verse(i);
            if(i > nbottels_stop){
                song << '\n';
            }
        }
        return song.str();
    }

    std::string verse(int nbottels){
        if(nbottels <= 0){
            return "No more bottles of beer on the wall, no more bottles of beer.\n"
                   "Go to the store and buy some more, 99 bottles of beer on the wall.\n";
        }
        
        std::ostringstream ss;
        ss.reserve(256); // Pre-allocate buffer
        
        const std::string bottles_current = p1(nbottels);
        const std::string bottles_next = p1(nbottels - 1);
        const std::string take_action = p2(nbottels);
        
        ss << bottles_current << " of beer on the wall, " << bottles_current << " of beer.\n"
           << "Take " << take_action << " down and pass it around, " << bottles_next << " of beer on the wall.\n";
        
        return ss.str();
    }

    std::string p1(int nbottels){
        switch(nbottels){
            case 0: return "no more bottles";
            case 1: return "1 bottle";
            default: return std::to_string(nbottels) + " bottles"; 
        }
    }

    std::string p2(int nbottels){
        return (nbottels == 1) ? "it" : "one";
    }

}  // namespace beer_song
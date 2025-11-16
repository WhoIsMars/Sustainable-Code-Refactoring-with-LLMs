#include "beer_song.h"
#include <iostream>
#include <sstream>
#include <boost/format.hpp>

namespace beer_song {
    using namespace std;
    using namespace boost;
    
    std::string sing(int nbottels_start, int nbottels_stop){
        string song;
        for(int i=nbottels_start; i >= nbottels_stop; i--){
            song += verse(i);
            if(i > nbottels_stop){
                song += "\n";
            }
        }
        return song;
    }

    std::string verse(int nbottels){
        if(nbottels <= 0){
            return string("No more bottles of beer on the wall, no more bottles of beer.\n"
            "Go to the store and buy some more, 99 bottles of beer on the wall.\n");
        }
        stringstream ss;
        ss << format("%1% of beer on the wall, %1% of beer.\n") % p1(nbottels);
        ss << format("Take %1% down and pass it around, %2% of beer on the wall.\n") % p2(nbottels) % p1(nbottels-1);
        return ss.str();
    }

    std::string p1(int nbottels){
        switch(nbottels){
            case 0: return string("no more bottles");
            case 1: return string("1 bottle");
            default: return std::to_string(nbottels) + " bottles"; 
        }
    }

    std::string p2(int nbottels){
        switch(nbottels){
            case 1: return string("it");
            default: return string("one");
        }
    }

}  // namespace beer_song

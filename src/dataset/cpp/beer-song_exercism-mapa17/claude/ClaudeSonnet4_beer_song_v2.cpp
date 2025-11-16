#include "beer_song.h"
#include <string>

namespace beer_song {
    
    std::string sing(int nbottels_start, int nbottels_stop){
        std::string song;
        song.reserve((nbottels_start - nbottels_stop + 1) * 150); // Pre-allocate memory
        
        for(int i = nbottels_start; i >= nbottels_stop; i--){
            song += verse(i);
            if(i > nbottels_stop){
                song += '\n';
            }
        }
        return song;
    }

    std::string verse(int nbottels){
        if(nbottels <= 0){
            return "No more bottles of beer on the wall, no more bottles of beer.\n"
                   "Go to the store and buy some more, 99 bottles of beer on the wall.\n";
        }
        
        std::string result;
        result.reserve(120); // Pre-allocate memory
        
        const std::string& bottles_current = p1(nbottels);
        const std::string& bottles_next = p1(nbottels - 1);
        const std::string& take_action = p2(nbottels);
        
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

    const std::string& p1(int nbottels){
        static const std::string no_more = "no more bottles";
        static const std::string one_bottle = "1 bottle";
        
        switch(nbottels){
            case 0: return no_more;
            case 1: return one_bottle;
            default: {
                static thread_local std::string cached_result;
                static thread_local int cached_value = -1;
                if(cached_value != nbottels) {
                    cached_result = std::to_string(nbottels) + " bottles";
                    cached_value = nbottels;
                }
                return cached_result;
            }
        }
    }

    const std::string& p2(int nbottels){
        static const std::string it_str = "it";
        static const std::string one_str = "one";
        
        return (nbottels == 1) ? it_str : one_str;
    }

}  // namespace beer_song